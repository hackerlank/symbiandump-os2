/*
* Copyright (c) 2007-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Interface definition for UPS dialog creator ECOM plug-in.
*
*/


/**
 @file
 @publishedPartner
 @released
*/

#ifndef DIALOGCREATOR_H
#define DIALOGCREATOR_H

#include <e32base.h>
#include <e32cmn.h>
#include <ups/policy.h>
#include <ups/ups.hrh>

namespace UserPromptService
	{
	class CClientEntity;
	class CFingerprint;
	class CPromptRequest;
	
	/**
	Abstract base class for dialog creator ECOM plug-ins.
	
	Dialog creators are responsible for generating and displaying prompt dialogs. Normally,
	the notifier framework (RNotifier) would be used to interact with the user interface layer.\n
	
	In addition to the data supplied by the system server the dialog creator may
	also include data from other servers such as AppArc or the SIS registry.
	Since retrieving this extra information may take an unpredictable amount of time the dialog
	creator PrepareDialog method is asynchronous to ensure the user prompt service is 
	not blocked.

	- A new dialog creator object is created for each request that requires a prompt. The object
	is destroyed after DisplayDialog has been called.
	*/			
	class CDialogCreator : public CActive
		{
	public:					
		IMPORT_C static CDialogCreator* NewL(const TUid& aDialogCreatorImplementationId);
		
		/**
		 Asynchronously retrieves and prepares the data needed to display the dialog.
		 
		 The const parameters aRequest, aPolicy, aFingerprints, aDialogCreatorParams persist
		 until after the the dialog creator has been destroyed; therefore, the dialog creator
		 may safely use pointers to this data internally.\n
		 
		 @param aRequest				The parameters supplied by the system server.
		 @param aPolicy					The policy being evaluated.
		 @param aFingerprints			The array of finger prints generated by the policy evaluator.\n
										This may be empty if the policy does not allow the Always or Never options.
		 @param aClientEntity			Identifies the entity within the client process that requested the service.\n
										NULL if the client processs is not an execution host.
		 @param	aDialogCreatorParams	Opaque data generated by the policy evaluator.
		 @param aStatus					The request object to complete once the dialog is ready.
		*/
		virtual void PrepareDialog(
			const CPromptRequest& aRequest, 
			const CPolicy& aPolicy,			
			const RPointerArray<CFingerprint>& aFingerprints,
			const CClientEntity* aClientEntity,
			const TAny* aDialogCreatorParams,
			TRequestStatus& aStatus) = 0;

		/**
		Asynchronously, displays the dialog created by PrepareDialog and interprets the result.	

		Note that the UPS server expects aOptionSelected to match one of the enabled options specified 
		in the policy entry which was passed into PrepareDialog. If no legal option is selected, it will be treated
		as a ENo.

		@param aOptionSelected	The option selected by the user.\n
								(OUT parameter)
		@param aFingerprint		A reference to a pointer used to return	the fingerprint to use in the new
								decision record if the Always or Never button was selected.\n
								Ownership is NOT transferred to the caller.\n
								(OUT parameter)
		@param aEvaluatorInfo	The value to write to the decision record's evaluatorInfo field if
								the Always or Never option was selected. The default 
								value for this field is 0x00000000 for a new record or the
								previous value if the policy evaluator forced a prompt to be
								displayed and a decision record already existed.\n
								(IN/OUT parameter)
		@param aStatus			The request object to complete once the dialog has been closed.
								
		 */
		virtual void DisplayDialog(
			CPolicy::TOptions& aOptionSelected,
			const CFingerprint*& aFingerprint,
			TUint& aEvaluatorInfo,
			TRequestStatus& aStatus) = 0;
					
		IMPORT_C TInt GetExtension(TUint aExtensionId, TAny*& a0, TAny* a1);		
		IMPORT_C ~CDialogCreator();		
	protected:
		IMPORT_C CDialogCreator();
		IMPORT_C virtual TInt Extension_(TUint aExtensionId, TAny*& a0, TAny* a1);
	private:
		TAny* iReserved;
		TUid iDtor_ID_Key;		// Required by ECOM
		};		
	}	

#endif // DIALGOCREATOR_H 