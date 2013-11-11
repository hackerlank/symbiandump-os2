/**
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
*/



/**
 @file te_dhcpTestStep2.h
*/
#if (!defined __DHCPTESTSTEP2_H__)
#define __DHCPTESTSTEP2_H__
#include <test/testexecutestepbase.h>
#include "te_dhcpTestServer.h"

DECLARE_DHCP_TEST_STEP(2_1);
DECLARE_DHCP_TEST_STEP(2_2);
DECLARE_DHCP_TEST_STEP(2_3);
DECLARE_DHCP_TEST_STEP(2_4);
DECLARE_DHCP_TEST_STEP(2_5);
DECLARE_DHCP_TEST_STEP(2_6);
DECLARE_DHCP_TEST_STEP(2_7);
DECLARE_DHCP_TEST_STEP(2_8);
DECLARE_DHCP_TEST_STEP(2_9);
DECLARE_DHCP_TEST_STEP(2_GetRaw);
DECLARE_DHCP_TEST_STEP(2_11);
DECLARE_DHCP_TEST_STEP(2_12);
DECLARE_DHCP_TEST_STEP(2_ClearMOFlag);
DECLARE_DHCP_TEST_STEP(2_NoRAandDHCPServ);
DECLARE_DHCP_TEST_STEP(2_GetSIPAddrViaDHCP);
DECLARE_DHCP_TEST_STEP(2_GetSIPAddrViaPCOBuffer);
DECLARE_DHCP_TEST_STEP(2_GetSIPDomain);
DECLARE_DHCP_TEST_STEP(2_GetSIPAddrFailure);
DECLARE_DHCP_TEST_STEP(2_GetSIPAddrBufferOverrun);
DECLARE_DHCP_TEST_STEP(2_GetSIPServerAddrIndexChecker);
DECLARE_DHCP_TEST_STEP(2_GetSIPServerAddrNegativeIndexChecker);
DECLARE_DHCP_TEST_STEP(2_23);
DECLARE_DHCP_TEST_STEP(2_24);
DECLARE_DHCP_TEST_STEP(2_25);

#ifdef SYMBIAN_NETWORKING_DHCP_MSG_HEADERS

DECLARE_DHCP_TEST_STEP(2_26);
DECLARE_DHCP_TEST_STEP(2_27);
DECLARE_DHCP_TEST_STEP(2_28);
DECLARE_DHCP_TEST_STEP(2_29);
DECLARE_DHCP_TEST_STEP(2_30);
DECLARE_DHCP_TEST_STEP(2_31);
DECLARE_DHCP_TEST_STEP(2_32);
DECLARE_DHCP_TEST_STEP(2_33);
DECLARE_DHCP_TEST_STEP(2_34);
DECLARE_DHCP_TEST_STEP(2_35);
DECLARE_DHCP_TEST_STEP(2_36);
DECLARE_DHCP_TEST_STEP(2_37);
DECLARE_DHCP_TEST_STEP(2_38);
DECLARE_DHCP_TEST_STEP(2_39);
DECLARE_DHCP_TEST_STEP(2_40);
DECLARE_DHCP_TEST_STEP(2_41);

#endif // SYMBIAN_NETWORKING_DHCP_MSG_HEADERS

/* Declarations for DHCP testing with Codenomicon tool*/

DECLARE_DHCP_TEST_STEP(Codenomicon1);
DECLARE_DHCP_TEST_STEP(Codenomicon2);
#ifdef SYMBIAN_TCPIPDHCP_UPDATE
/* PREQ1898 DHCP IPV6(option 23 and 24 test cases) */
DECLARE_DHCP_TEST_STEP(2_DomainSearchList_Test1);
DECLARE_DHCP_TEST_STEP(2_DomainSearchList_Test2);
DECLARE_DHCP_TEST_STEP(2_DomainSearchList_Test3);
DECLARE_DHCP_TEST_STEP(2_DomainSearchList_Test4);
DECLARE_DHCP_TEST_STEP(2_DomainSearchList_Test5);

DECLARE_DHCP_TEST_STEP(2_DNSServerList_Test1);
DECLARE_DHCP_TEST_STEP(2_DNSServerList_Test2);
DECLARE_DHCP_TEST_STEP(2_DNSServerList_Test3);
DECLARE_DHCP_TEST_STEP(2_DNSServerList_Test4);
DECLARE_DHCP_TEST_STEP(2_DNSServerList_Test5);

DECLARE_DHCP_TEST_STEP(2_MultipleParams_Test1);
DECLARE_DHCP_TEST_STEP(2_MultipleParams_Test2);
DECLARE_DHCP_TEST_STEP(2_MultipleParams_Test3);
DECLARE_DHCP_TEST_STEP(2_MultipleParams_Test4);
DECLARE_DHCP_TEST_STEP(2_MultipleParams_Test5);

DECLARE_DHCP_TEST_STEP(2_GetRaw_Test1);
DECLARE_DHCP_TEST_STEP(2_GetRaw_Test2);
#endif //SYMBIAN_TCPIPDHCP_UPDATE 

#endif

