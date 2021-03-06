/*
* Copyright (c) 1997-2010 Nokia Corporation and/or its subsidiary(-ies).
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
* Adheres to the UsbMan USB Class Controller API and talks to C32
* to manage the stub3.CSY that is used to provide a virtual
* serial port service to clients
*
*/

/**
 @file
*/

#include <usb_std.h>
#include <es_ini.h>
#include <d32usbc.h>
#include <usb/usbmaninternalconstants.h>
#include "Stub3CC.h"

#ifdef __FLOG_ACTIVE
_LIT8(KLogComponent, "STUB3CC");
#endif



#include "OstTraceDefinitions.h"
#ifdef OST_TRACE_COMPILER_IN_USE
#include "Stub3CCTraces.h"
#endif

 

// Panic category 
_LIT( Kstub3CcPanicCategory, "Usbstub3Cc" );


/**
 * Panic codes for the USB stub3 Class Controller.
 */
enum Tstub3CcPanic
	{
	/** Class called while in an illegal state */
	EBadApiCall = 0,
	/** Asynchronous function called (not needed, as all requests complete synchronously) */
	EUnusedFunction = 1,
	/** Error reading ini file. */
	EPanicBadIniFile = 2,		
	/** Bad value for the iNumberOfstub3Functions member.*/
	EPanicBadNumberOfstub3Functions = 3,
	
	EPanicUnexpectedStatus,
	EPanicUnexpectedState

	};
	
_LIT16(KIfcName, "SubCC 1 Interface");
const TInt KMaxPacketTypeInterrupt = 64;	
const TInt KPollInterval  = 128; 




/**
 * Constructs a CUsbstub3ClassController object
 *
 * @param	aOwner	USB Device that owns and manages the class
 *
 * @return	A new CUsbstub3ClassController object
 */
CUsbstub3ClassController* CUsbstub3ClassController::NewL(
	MUsbClassControllerNotify& aOwner)
	{
	CUsbstub3ClassController* r = new (ELeave) CUsbstub3ClassController(aOwner);
	CleanupStack::PushL(r);
	r->ConstructL();
	CleanupStack::Pop();
	return r;
	}

/**
 * Destructor
 */
CUsbstub3ClassController::~CUsbstub3ClassController()
	{
	Cancel();

	iTimer.Close();

#ifndef __WINS__	
	iLdd.Close();
#endif

	}



/**
 * Constructor.
 *
 * @param	aOwner	USB Device that owns and manages the class
 */
CUsbstub3ClassController::CUsbstub3ClassController(
	MUsbClassControllerNotify& aOwner)
	: CUsbClassControllerPlugIn(aOwner, Kstub3StartupPriority),
	iStartDelay(Kstub3CCDefaultDelay),
	iStopDelay(Kstub3CCDefaultDelay),
	iFailToStart(EFalse),
	iFailToStop(EFalse)	

	{
	iTimer.CreateLocal();
	}



/**
 * 2nd Phase Construction.
 */
void CUsbstub3ClassController::ConstructL()
	{
	//read INI file
	TInt ret;
	CESockIniData* ini = 0;
	_LIT(KIniFile, "c:\\testdata\\config\\stub3cc.ini");
	TRAP(ret, ini=CESockIniData::NewL(KIniFile));	
	if(ret!=KErrNone)		
		return;	

	CleanupStack::PushL(ini);
	
	TInt val;
	if ((ini->FindVar(_L("0x10203289"),_L("StartDelay"), val)))
		{
		iStartDelay = val;
		}
	if ((ini->FindVar(_L("0x10203289"),_L("StopDelay"), val)))
		{
		iStopDelay = val;
		}
	if ((ini->FindVar(_L("0x10203289"),_L("FailToStart"), val)) && val!=0)
		{
		iFailToStart = ETrue;
		}
	if ((ini->FindVar(_L("0x10203289"),_L("FailToStop"), val)) && val!=0 )
		{
		iFailToStop = ETrue;
		}
	CleanupStack::PopAndDestroy(ini);						
	}

/**
 * Called by UsbMan when it wants to start the USB stub3 class. This always
 * completes immediately.
 *
 * @param aStatus The caller's request status, filled in with an error code
 */
void CUsbstub3ClassController::Start(TRequestStatus& aStatus)
	{
    OstTraceFunctionEntry0( CUSBSTUB3CLASSCONTROLLER_START_ENTRY );
    
	aStatus = KRequestPending;
	iReportStatus = &aStatus;
	//If we are already started then just complete the request.
	if (iState == EUsbServiceStarted)
		{
		User::RequestComplete(iReportStatus, KErrNone);
		OstTraceFunctionExit0( CUSBSTUB3CLASSCONTROLLER_START_EXIT );
		return;
		}

	if (iFailToStart)
		{
		User::RequestComplete(iReportStatus, KErrGeneral);
		OstTraceFunctionExit0( CUSBSTUB3CLASSCONTROLLER_START_EXIT_DUP1 );
		return;
		}
	
	iState = EUsbServiceStarting;
	
#ifndef __WINS__	
	TInt ret = iLdd.Open(0);
	OstTrace1( TRACE_NORMAL, CUSBSTUB3CLASSCONTROLLER_START, _L8("Open LDD, ret=%d"), ret );
	
	ret = SetUpInterface();
	OstTrace1( TRACE_NORMAL, CUSBSTUB3CLASSCONTROLLER_START_DUP1, 
	        _L8("SetUpInterface(), ret=%d"), ret );
	
#endif	


	iTimer.After(iStatus, iStartDelay*1000);  //convert from usec to msec
	SetActive();
	OstTraceFunctionExit0( CUSBSTUB3CLASSCONTROLLER_START_EXIT_DUP2 );
	}

/**
 * Called by UsbMan when it wants to stop the USB stub3 class.
 *
 * @param aStatus The caller's request status: always set to KErrNone
 */
void CUsbstub3ClassController::Stop(TRequestStatus& aStatus)
	{
	OstTraceFunctionEntry0( CUSBSTUB3CLASSCONTROLLER_STOP_ENTRY );
	
	aStatus = KRequestPending;
	iReportStatus = &aStatus;
	//If we are already idle then just complete the request.
	if (iState == EUsbServiceIdle)
		{
		User::RequestComplete(iReportStatus, KErrNone);
		OstTraceFunctionExit0( CUSBSTUB3CLASSCONTROLLER_STOP_EXIT );
		return;
		}

	if (iFailToStop)
		{
		User::RequestComplete(iReportStatus, KErrGeneral);
		OstTraceFunctionExit0( CUSBSTUB3CLASSCONTROLLER_STOP_EXIT_DUP1 );
		return;
		}

	iState = EUsbServiceStopping;

#ifndef __WINS__	
	iLdd.Close();
#endif

	
	iTimer.After(iStatus, iStopDelay*1000);  //convert from usec to msec
	SetActive();
	OstTraceFunctionExit0( CUSBSTUB3CLASSCONTROLLER_STOP_EXIT_DUP2 );
	}

/**
 * Gets information about the descriptor which this class provides.
 *
 * @param aDescriptorInfo Descriptor info structure filled in by this function
 */
void CUsbstub3ClassController::GetDescriptorInfo(TUsbDescriptor& aDescriptorInfo) const
	{
    OstTraceFunctionEntry0( CUSBSTUB3CLASSCONTROLLER_GETDESCRIPTORINFO_ENTRY );
    
	aDescriptorInfo.iLength = Kstub3DescriptorLength;
	aDescriptorInfo.iNumInterfaces = Kstub3NumberOfInterfacesPerstub3Function;
	
	OstTraceFunctionExit0( CUSBSTUB3CLASSCONTROLLER_GETDESCRIPTORINFO_EXIT );
	}


/**
 * Standard active object RunL. 
 */
void CUsbstub3ClassController::RunL()
	{
    OstTraceFunctionEntry0( CUSBSTUB3CLASSCONTROLLER_RUNL_ENTRY );
    
    if(iStatus != KErrNone)
        {
            OstTrace1( TRACE_FATAL, CUSBSTUB3CLASSCONTROLLER_RUNL, 
                    "CUsbstub3ClassController::RunL panic with error %d", EPanicUnexpectedStatus );
            __ASSERT_DEBUG(EFalse,User::Panic(Kstub3CcPanicCategory,EPanicUnexpectedStatus));
        }
	switch (iState)
		{
		case EUsbServiceStarting:
			iState = EUsbServiceStarted;
			break;
		case EUsbServiceStopping:
			iState = EUsbServiceIdle;
			break;
		default:	
		    OstTrace1( TRACE_FATAL, CUSBSTUB3CLASSCONTROLLER_RUNL_DUP1, 
		             "CUsbstub3ClassController::RunL panic with error %d", EPanicUnexpectedStatus );
		    User::Panic(Kstub3CcPanicCategory,EPanicUnexpectedStatus);
		}
	*iReportStatus = KErrNone;	
	User::RequestComplete(iReportStatus, iStatus.Int());	
	OstTraceFunctionExit0( CUSBSTUB3CLASSCONTROLLER_RUNL_EXIT );
	}

/**
 * Standard active object cancellation function. Never called because this
 * class has no asynchronous requests.
 */
void CUsbstub3ClassController::DoCancel()
	{

	if (IsActive())
		{
		iTimer.Cancel();	
		}
	switch (iState)
	{
		case EUsbServiceStarting:
			iState = EUsbServiceIdle;
			break;
		case EUsbServiceStopping:
			iState = EUsbServiceStarted;
			break;
		default:
		    OstTrace1( TRACE_FATAL, CUSBSTUB3CLASSCONTROLLER_DOCANCEL, 
		            "CUsbstub3ClassController::DoCancel panic with error %d", EPanicUnexpectedStatus );
		    User::Panic(Kstub3CcPanicCategory,EPanicUnexpectedStatus);
	}
	*iReportStatus = KErrNone;		
	User::RequestComplete(iReportStatus, KErrCancel);	
	}

/**
 * Standard active object error function. Never called because this class has
 * no asynchronous requests, and hence its RunL is never called.
 *
 * @param aError The error code (unused)
 * @return Always KErrNone to avoid an active scheduler panic
 */
TInt CUsbstub3ClassController::RunError(TInt /*aError*/)
	{
    OstTrace1( TRACE_FATAL, CUSBSTUB3CLASSCONTROLLER_RUNERROR, 
             "CUsbstub3ClassController::RunError panic with error %d", EUnusedFunction );
    __ASSERT_DEBUG(EFalse,User::Panic(Kstub3CcPanicCategory,EUnusedFunction));
	return KErrNone;
	}

TInt CUsbstub3ClassController::SetUpInterface()
/**
 * Set up the interface for use. This involves finding a "Interrupt IN" 
 * endpoint and, if found, configuring the interface.
 */
	{
    OstTraceFunctionEntry0( CUSBSTUB3CLASSCONTROLLER_SETUPINTERFACE_ENTRY );
    
	TUsbDeviceCaps dCaps;
	TInt ret = iLdd.DeviceCaps(dCaps);
	OstTrace0( TRACE_NORMAL, CUSBSTUB3CLASSCONTROLLER_SETUPINTERFACE,
	        _L8("\tchecking result of DeviceCaps"));
	
	if ( ret )
		{
        OstTrace1( TRACE_ERROR, CUSBSTUB3CLASSCONTROLLER_SETUPINTERFACE_DUP1, 
                _L8("<<CCdcControlInterface::SetUpInterface ret=%d"), ret );
        
		OstTraceFunctionExit0( CUSBSTUB3CLASSCONTROLLER_SETUPINTERFACE_EXIT );
		return ret;
		}

	const TUint KRequiredNumberOfEndpoints = 1; // in addition to endpoint 0.

	const TUint totalEndpoints = static_cast<TUint>(dCaps().iTotalEndpoints);
	OstTrace1( TRACE_NORMAL, CUSBSTUB3CLASSCONTROLLER_SETUPINTERFACE_DUP2, 
	        _L8("\tiTotalEndpoints = %d"), totalEndpoints );
	
	if ( totalEndpoints < KRequiredNumberOfEndpoints )
		{
        OstTrace1( TRACE_ERROR, CUSBSTUB3CLASSCONTROLLER_SETUPINTERFACE_DUP3, 
                _L8("<<CCdcControlInterface::SetUpInterface ret=%d"), KErrGeneral );
        
		OstTraceFunctionExit0( CUSBSTUB3CLASSCONTROLLER_SETUPINTERFACE_EXIT_DUP1 );
		return KErrGeneral;
		}
	
	// Endpoints
	TUsbcEndpointData data[KUsbcMaxEndpoints];
	TPtr8 dataptr(reinterpret_cast<TUint8*>(data), sizeof(data), sizeof(data));
	ret = iLdd.EndpointCaps(dataptr);
	OstTrace0( TRACE_NORMAL, CUSBSTUB3CLASSCONTROLLER_SETUPINTERFACE_DUP4,
	        _L8("\tchecking result of EndpointCaps"));
	
	if ( ret )
		{
        OstTrace1( TRACE_ERROR, CUSBSTUB3CLASSCONTROLLER_SETUPINTERFACE_DUP5, 
                _L8("<<CCdcControlInterface::SetUpInterface ret=%d"), ret );
        
		OstTraceFunctionExit0( CUSBSTUB3CLASSCONTROLLER_SETUPINTERFACE_EXIT_DUP2 );
		return ret;
		}

	// Set the active interface
	TUsbcInterfaceInfoBuf ifc;
	TBool epFound = EFalse;
	for ( TUint i = 0 ; i < totalEndpoints ; i++ )
		{
		const TUsbcEndpointCaps* caps = &data[i].iCaps;
		if(!caps)
		    {
                OstTrace1( TRACE_FATAL, CUSBSTUB3CLASSCONTROLLER_SETUPINTERFACE_DUP6, 
                        "CUsbstub3ClassController::SetUpInterface panic with error %d", 
                        EPanicUnexpectedStatus );
                __ASSERT_DEBUG(EFalse,User::Panic(Kstub3CcPanicCategory,EPanicUnexpectedStatus));
		    }

		if (data[i].iInUse)
			{
			continue;
			}

		if ((caps->iTypesAndDir & (KUsbEpTypeInterrupt | KUsbEpDirIn)) == 
			(KUsbEpTypeInterrupt | KUsbEpDirIn))
			{
			// EEndpoint1 is interrupt endpoint
			ifc().iEndpointData[0].iType  = KUsbEpTypeInterrupt;
			ifc().iEndpointData[0].iDir   = KUsbEpDirIn; 

			//get the max packet size it can potentially support
			//it's possible that it can support Isoch (1023) which is greater
			//than max for Int at 64
			TInt maxSize = Min(caps->MaxPacketSize(), KMaxPacketTypeInterrupt);
			
			ifc().iEndpointData[0].iSize  = maxSize;

			ifc().iEndpointData[0].iInterval = KPollInterval; 
			epFound = ETrue;
			break;
			}
		}
	OstTrace0( TRACE_NORMAL, CUSBSTUB3CLASSCONTROLLER_SETUPINTERFACE_DUP7, _L8("\tchecking epFound"));
	
	if ( !epFound )
		{
        OstTrace1( TRACE_ERROR, CUSBSTUB3CLASSCONTROLLER_SETUPINTERFACE_DUP8, 
                _L8("<<CCdcControlInterface::SetUpInterface ret=%d"), KErrGeneral);
        
		OstTraceFunctionExit0( CUSBSTUB3CLASSCONTROLLER_SETUPINTERFACE_EXIT_DUP3 );
		return KErrGeneral;
		}

	TName ifcName(KIfcName);
	ifc().iString = &ifcName;
	ifc().iTotalEndpointsUsed = KRequiredNumberOfEndpoints;
	// Codes taken from USBCDC 1.1.
	ifc().iClass.iClassNum	  = 0x02; // Table 15- Communication Interface Class
	ifc().iClass.iSubClassNum = 0x02; // Table 16- Abstract Control Model
	ifc().iClass.iProtocolNum = 0x01; // Table 17- Hayes compatible

	OstTrace0( TRACE_NORMAL, CUSBSTUB3CLASSCONTROLLER_SETUPINTERFACE_DUP9,
	        _L8("\tabout to call SetInterface"));
	
	// Zero effectively indicates that alternate interfaces are not used.
	ret = iLdd.SetInterface(0, ifc);

	OstTrace1( TRACE_NORMAL, CUSBSTUB3CLASSCONTROLLER_SETUPINTERFACE_DUP10, 
	        _L8("<<CCdcControlInterface::SetUpInterface ret=%d"), ret );
	
	OstTraceFunctionExit0( CUSBSTUB3CLASSCONTROLLER_SETUPINTERFACE_EXIT_DUP4 );
	return ret;
	}

//
// End of file
