/*
* Copyright (c) 2006-2010 Nokia Corporation and/or its subsidiary(-ies).
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


/**
 @file
 @internalComponent
 @released
*/

#ifndef __PLUGINENTRY_H__
#define __PLUGINENTRY_H__

#include <cryptospi/cryptoparams.h>
#include <e32cmn.h>
#include <cryptospi/cryptospidef.h>
#include <cryptospi/keys.h>
#include <cryptospi/hashplugin.h>
#include <cryptospi/randomplugin.h>
#include <cryptospi/symmetriccipherplugin.h>
#include <cryptospi/asymmetriccipherplugin.h>
#include <cryptospi/signerplugin.h>
#include <cryptospi/verifierplugin.h>
#include <cryptospi/keypairgeneratorplugin.h>
#include <cryptospi/keyagreementplugin.h>

#ifdef SYMBIAN_SDP_IPSEC_VOIP_SUPPORT
#include <cryptospi/macplugin.h>
#endif

using namespace CryptoSpi;

class CCryptoPluginEntry
	{
public:

	/**
	Enumerates the set of plug-ins supported by the module for a given interface
	e.g. all of the hash plug-ins.

	@param aInterface The UID of the plug-in interface type. If the UID is not recognised
	then the NULL pointer must be returned.
	@param aNumPlugins The number of plug-in characteristics objects in the result.
	@param A pointer to an array of characteristics objects. The SPI casts this to
	the expected sub-class of TCharacteristics for the specified interface UID.
	*/
	IMPORT_C static const TCharacteristics** Enumerate(TUid aInterface, TInt& aNumPlugins);

	/**
    Retrieves the extended characteristics about a given implementation of an
    algorithm within the current plug-in DLL.

    @param aImplementationUid The UID of the implementation requested
    @return A pointer to the extended characteristics, allocated on the heap,
    which should be deleted once the caller has finished with it.
	*/
	IMPORT_C static void GetExtendedCharacteristicsL(TUid aImplementationUid, CExtendedCharacteristics*&);

	/**
	Creates a new instance of an asymmetric cipher

	@param aPlugin A reference to a pointer that should be set to point to 
	the new asymmetric cipher object.
	@param aImplementationId The UID of the asymmetric cipher plug-in to instantiate.
	@param aKey The encryption/decryption key.
	@param aAlgorithmParams The parameters that are specific to a particular 
	algorithm. This is for extendibility and will normally be null.
	@return KErrNone if successful; otherwise, a system wide error code.
	*/
	IMPORT_C static void CreateAsymmetricCipherL(MAsymmetricCipher*& aPlugin,
												TUid aImplementationId,
												const CKey& aKey,
												TUid aCryptoMode,
												TUid aPaddingMode,
												const CCryptoParams* aAlgorithmParams);

	/**
	Creates a new instance of an asymmetric signer.

	@param aPlugin A reference to a pointer that should be set to point to 
	the new asymmetric signer object.
	@param aImplementationId The UID of the signer plug-in to instantiate.
	@param aKey The signing key.
	@param aAlgorithmParams The parameters that are specific to a particular 
	algorithm. This is for extendibility and will normally be null.
	@return KErrNone if successful; otherwise, a system wide error code.
	*/
	IMPORT_C static void CreateAsymmetricSignerL(MSigner*& aPlugin,
												TUid aImplementationId,
												const CKey& aKey,
												TUid aPaddingMode,
												const CCryptoParams* aAlgorithmParams);

	/**
	Creates a new instance of an asymmetric verifier.

	@param aPlugin A reference to a pointer that should be set to point to 
	the new asymmetric verifier object.
	@param aImplementationId The UID of the verifier plug-in to instantiate.
	@param aKey The key to verify the signature with.
	@param aAlgorithmParams The parameters that are specific to a particular 
	algorithm. This is for extendibility and will normally be null.
	@return KErrNone if successful; otherwise, a system wide error code.
	*/
	IMPORT_C static void CreateAsymmetricVerifierL(MVerifier*& aPlugin,
												TUid aImplementationId,
												const CKey& aKey,
												TUid aPaddingMode,
												const CCryptoParams* aAlgorithmParams);


									
	/**
	Creates a new instance of a Hash object.

	@param aPlugin A reference to a pointer that should be set to point to 
	the new hash object.
	@param aImplementationId The UID of the hash plug-in to instantiate.
	@param aAlgorithmParams The parameters that are specific to a particular 
	algorithm. This is for extendibility and will normally be null.
	@return KErrNone if successful; otherwise, a system wide error code.
	*/
	IMPORT_C static void CreateHashL(MHash*& aPlugin,
							TUid aImplementationId,
							TUid aOperationMode,
							const CKey* aKey,
							const CCryptoParams* aAlgorithmParams);

#ifdef SYMBIAN_SDP_IPSEC_VOIP_SUPPORT
	/**
	 * Creates a new instance of a Hash object.
	 *
	 * @param aPlugin A reference to a pointer that should be set to point to 
	 * the new hash object.
	 * @param aImplementationId The UID of the hash plug-in to instantiate.
	 * @param aAlgorithmParams The parameters that are specific to a particular 
	 * algorithm. This is for extendibility and will normally be null.
	 * @return KErrNone if successful; otherwise, a system wide error code.
	 */
	IMPORT_C static void CreateHashL(MHash*& aPlugin,
									 TUid aImplementationId,
									 const CCryptoParams* aAlgorithmParams);
#endif

	/**
	Creates a new instance of a Random object.

	@param aPlugin A reference to a pointer that should be set to point to the new random object.
	@param aImplementationId The UID of the random plug-in to instantiate.
	@param aAlgorithmParams The parameters that are specific to a particular 
	algorithm. This is for extendibility and will normally be null.
	@return KErrNone if successful; otherwise, a system wide error code.
	*/
	IMPORT_C static void CreateRandomL(MRandom*& aPlugin,
									TUid aImplementationId,
									const CCryptoParams* aAlgorithmParams);


	/**
	Creates a new instance of a key agreement system.

	@param aPlugin A reference to a pointer that should be set to point to 
	the new asymmetric key pair generator object.
	@param aImplementationId The UID of the key agreement plug-in to instantiate.
	@param aKey The private key to combine with the other parties public key
	during the agreement.
	@param aAlgorithmParams The parameters that are specific to a particular 
	algorithm. This is for extendibility and will normally be null.
	@return KErrNone if successful; otherwise, a system wide error code.		   
	*/
	IMPORT_C static void CreateKeyAgreementL(MKeyAgreement*& aPlugin,
											TUid aImplementationId,
											const CKey& aPrivateKey,
											const CCryptoParams* aAlgorithmParams);

	/**
	Creates a new instance of an asymmetric key pair generator.

	@param aPlugin A reference to a pointer that should be set to point to 
	the new asymmetric key pair generator object.
	@param aImplementationId The UID of the verifier plug-in to instantiate.
	@param aAlgorithmParams The parameters that are specific to a particular 
	algorithm. This is for extendibility and will normally be null.
	@return KErrNone if successful; otherwise, a system wide error code.
	*/
	IMPORT_C static void CreateKeyPairGeneratorL(MKeyPairGenerator*& aPlugin,
												TUid aImplementationId,
												const CCryptoParams* aAlgorithmParams);
									
	/**
	Creates a new instance of a symmetric cipher

	@param aPlugin A reference to a pointer that should be set to point to 
	the new asymmetric object.
	@param aImplementationId The UID of the symmetric cipher plug-in to instantiate.
	@param aKey The encryption/decryption key.
	@param aCryptoMode Encrypt or Decrypt.
	@param aOperationMode the block cipher mode to use ECB, CBC, CTR etc
	@param aPadding the padding scheme to use.
	@param aAlgorithmParams The parameters that are specific to a particular 
	algorithm. This is for extendibility and will normally be null.
	@return KErrNone if successful; otherwise, a system wide error code.
	*/
	IMPORT_C static void CreateSymmetricCipherL(MSymmetricCipher*& aPlugin,
											TUid aImplementationId,
											const CKey& aKey,
											TUid aCryptoMode,
											TUid aOperationMode,
											TUid aPadding,
											const CCryptoParams* aAlgorithmParams);

#ifdef SYMBIAN_SDP_IPSEC_VOIP_SUPPORT
	/**
	 * Create a CMac instance (if implementation is software based)
	 *
	 * @param aMac The pointer to CMac
	 * @param aImplementationId The specific hash or cipher plug-in to instantiate..
	 * @param aKey             	The key for calculating message authentication code value. 
	 *                         	Based on the algorithm used we will define the properties of the key.
	 * @param aAlgorithmParams 	The parameters that are specific to a particular 
	 *                         	algorithm. This is for extendibility and will normally be null. 	
	 * @return                 	KErrNone if successful; otherwise, a system wide error code.
	 */
	IMPORT_C static void CreateMacL(MMac*& aPlugin,
									const TUid aImplementationId,
									const CKey& aKey,
									const CCryptoParams* aAlgorithmParams);
#endif
	
	
	/**
	Creates a new instance of a Random object.

	@param aPlugin A reference to a pointer that should be set to point to the new random object.
	@param aImplementationId The UID of the random plug-in to instantiate.
	@param aAlgorithmParams The parameters that are specific to a particular 
	algorithm. This is for extendibility and will normally be null.
	@return KErrNone if successful; otherwise, a system wide error code.
	
	IMPORT_C static void CreateAsyncRandomL(MAsyncRandom*& aPlugin,
									TUid aImplementationId,
									const CCryptoParams* aAlgorithmParams);
									
	*/										
	/**
	Creates a new instance of a Hash object.

	@param aPlugin A reference to a pointer that should be set to point to 
	the new hash object.
	@param aImplementationId The UID of the hash plug-in to instantiate.
	@param aAlgorithmParams The parameters that are specific to a particular 
	algorithm. This is for extendibility and will normally be null.
	@return KErrNone if successful; otherwise, a system wide error code.
	
	IMPORT_C static void CreateAsyncHashL(MAsyncHash*& aPlugin,
							TUid aImplementationId,
							const CCryptoParams* aAlgorithmParams);

	*/


	/**
	Creates a new instance of a symmetric cipher

	@param aPlugin A reference to a pointer that should be set to point to 
	the new asymmetric object.
	@param aImplementationId The UID of the symmetric cipher plug-in to instantiate.
	@param aKey The encryption/decryption key.
	@param aAlgorithmParams The parameters that are specific to a particular 
	algorithm. This is for extendibility and will normally be null.
	@return KErrNone if successful; otherwise, a system wide error code.

	IMPORT_C static void CreateAsyncSymmetricCipherL(MAsyncSymmetricCipher*& aPlugin,
											TUid aImplementationId,
											const CKey& aKey,
											TUid aMode,
											TUid aPadding,
											const CCryptoParams* aAlgorithmParams);

	*/
	/**
	Creates a new instance of an asymmetric cipher

	@param aPlugin A reference to a pointer that should be set to point to 
	the new asymmetric cipher object.
	@param aImplementationId The UID of the asymmetric cipher plug-in to instantiate.
	@param aKey The encryption/decryption key.
	@param aAlgorithmParams The parameters that are specific to a particular 
	algorithm. This is for extendibility and will normally be null.
	@return KErrNone if successful; otherwise, a system wide error code.
	
	IMPORT_C static void CreateAsyncAsymmetricCipherL(MAsyncAsymmetricCipher*& aPlugin,
												TUid aImplementationId,
												const CKey& aKey,
												const CCryptoParams* aAlgorithmParams);



*/
	/**
	Creates a new instance of an asymmetric signer.

	@param aPlugin A reference to a pointer that should be set to point to 
	the new asymmetric signer object.
	@param aImplementationId The UID of the signer plug-in to instantiate.
	@param aKey The signing key.
	@param aAlgorithmParams The parameters that are specific to a particular 
	algorithm. This is for extendibility and will normally be null.
	@return KErrNone if successful; otherwise, a system wide error code.
	
	IMPORT_C static void CreateAsyncAsymmetricSignerL(MAsyncSigner*& aPlugin,
												TUid aImplementationId,
												const CKey& aKey,
												const CCryptoParams* aAlgorithmParams);
	*/
	/**
	Creates a new instance of an asymmetric verifier.

	@param aPlugin A reference to a pointer that should be set to point to 
	the new asymmetric verifier object.
	@param aImplementationId The UID of the verifier plug-in to instantiate.
	@param aKey The key to verify the signature with.
	@param aAlgorithmParams The parameters that are specific to a particular 
	algorithm. This is for extendibility and will normally be null.
	@return KErrNone if successful; otherwise, a system wide error code.

	IMPORT_C static void CreateAsyncAsymmetricVerifierL(MAsyncVerifier*& aPlugin,
												TUid aImplementationId,
												const CKey& aKey,
												const CCryptoParams* aAlgorithmParams);


	*/
	/**
	Creates a new instance of a key agreement system.

	@param aPlugin A reference to a pointer that should be set to point to 
	the new asymmetric key pair generator object.
	@param aImplementationId The UID of the key agreement plug-in to instantiate.
	@param aKey The private key to combine with the other parties public key
	during the agreement.
	@param aAlgorithmParams The parameters that are specific to a particular 
	algorithm. This is for extendibility and will normally be null.
	@return KErrNone if successful; otherwise, a system wide error code.		   

	IMPORT_C static void CreateAsyncKeyAgreementL(MAsyncKeyAgreement*& aPlugin,
											TUid aImplementationId,
											const CKey& aPrivateKey,
											const CCryptoParams* aAlgorithmParams);
	*/
	/**
	Creates a new instance of an asymmetric key pair generator.

	@param aPlugin A reference to a pointer that should be set to point to 
	the new asymmetric key pair generator object.
	@param aImplementationId The UID of the verifier plug-in to instantiate.
	@param aAlgorithmParams The parameters that are specific to a particular 
	algorithm. This is for extendibility and will normally be null.
	@return KErrNone if successful; otherwise, a system wide error code.
	
	
	IMPORT_C static void CreateAsyncKeyPairGeneratorL(MAsyncKeyPairGenerator*& aPlugin,
												TUid aImplementationId,
												const CCryptoParams* aAlgorithmParams);
	*/
	};		

#endif // __PLUGINENTRY_H__
