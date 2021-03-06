// Copyright (c) 2004-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
// DBMS security policy - testing new APIs.
// This test app has "PowerMgmt" (TABLE A: READ) capability, which allows it to
// read data from table A.
// The UID policy file is 11335579.spd.
// The test uses C:TESTDB.DB secure shared database, which has tables A, B and C, each of them
// with at least one record.
// Please, ensure that t_dbenvcreate test is executed before t_dbplatsec<N>/t_dbplatsecperf tests!
// Please, ensure that t_dbenvdestroy test is executed after t_dbplatsec<N>/t_dbplatsecperf tests!
// 
//

#include <e32test.h>
#include <d32dbms.h>
#include "t_dbplatsecutl.h"

const TUid KSecureDbUid = {0x11335579};
_LIT(KSecure,	"SECURE");
_LIT(KDbName,	"C:TestDB.DB");
_LIT(KTblNameA,	"A");
_LIT(KTblNameB,	"B");
_LIT(KTblNameC,	"C");

static RTest 				TheTest(_L("t_dbplatsec3: DBMS platform security testing - 3"));
static RDbs 				TheDbs;
static RDbNamedDatabase 	TheDb;
static RDbTable 			TheTbl;
static RDbView 				TheView;

TDBSCUtils 	TheDbscUtils(TheTest, NULL);

/**
@SYMTestCaseID SYSLIB-DBMS-CT-0015
@SYMTestCaseDesc OPen table test.
				 This test app has "PowerMgmt" (TABLE A: READ) capability, which allows it to
				 read data from table A. B and C tables can be read too, because they do
				 not have read security policy. The attempts to open A, B and C tables in
				 insert/update mode must fail.
@SYMTestPriority High
@SYMTestActions  Open table test.
@SYMTestExpectedResults The test must not fail.
@SYMREQ REQ2429
                 DBMS shall provide an API to apply security policies to database tables.
*/
static void TblOpenL()
	{
	TheTest.Printf(_L("An attempt to open table A\n"));
	//The test must fail, because the test app cannot satisfy table A, policy W.
	TInt err = TheTbl.Open(TheDb, KTblNameA);
	TEST2(err, KErrPermissionDenied);
	//The test must pass, because the test app can satisfy table A, policy R.
	err = TheTbl.Open(TheDb, KTblNameA, RDbRowSet::EReadOnly);
	TEST2(err, KErrNone);
	TheTbl.Close();

	TheTest.Printf(_L("An attempt to open table B\n"));
	//The test must fail, because the test app cannot satisfy table B, policy W.
	err = TheTbl.Open(TheDb, KTblNameB);
	TEST2(err, KErrPermissionDenied);
	//The test must pass, because table B has no R policy.
	err = TheTbl.Open(TheDb, KTblNameB, RDbRowSet::EReadOnly);
	TEST2(err, KErrNone);
	TheTbl.Close();

	TheTest.Printf(_L("An attempt to open table C\n"));
	//The test must fail, because the test app cannot satisfy table C, policy W.
	err = TheTbl.Open(TheDb, KTblNameC);
	TEST2(err, KErrPermissionDenied);
	//The test must pass, because table C has no R policy.
	err = TheTbl.Open(TheDb, KTblNameC, RDbRowSet::EReadOnly);
	TEST2(err, KErrNone);
	TheTbl.Close();
	}

/**
@SYMTestCaseID SYSLIB-DBMS-CT-0016
@SYMTestCaseDesc R/W operations at a table level.
				 This test app has "PowerMgmt" (TABLE A: READ) capability, which allows it to
				 read data from table A. B and C tables can be read too, because they do
				 not have read security policy.
@SYMTestPriority High
@SYMTestActions  R/W table operations.
@SYMTestExpectedResults The test must not fail.
@SYMREQ REQ2429
                 DBMS shall provide an API to apply security policies to database tables.
*/
static void TblRWL()
	{
	TheTest.Printf(_L("Table A - Write\n"));
	TInt err = TheTbl.Open(TheDb, KTblNameA, RDbRowSet::EReadOnly);
	TEST2(err, KErrNone);
	//The test must fail, because the test app cannot satisfy table A, policy W.
	TRAP(err, TheTbl.InsertL());
	TEST2(err, KErrPermissionDenied);
	err = TheDb.Execute(_L("UPDATE A SET DATA1 = 400 WHERE ID < 10"));
	TEST2(err, KErrPermissionDenied);

	TheTest.Printf(_L("Table A - Read\n"));
	//The test must pass, because the test app can satisfy table A, policy R.
	TBool res = EFalse;
	TRAP(err, res = TheTbl.FirstL());
	TEST2(err, KErrNone);
	TEST(res);
	TInt cnt = TheTbl.CountL();
	TEST(cnt > 0);
	err = TheView.Prepare(TheDb, TDbQuery(_L("SELECT * FROM A")));
	TEST2(err, KErrNone);
	cnt = TheView.CountL();
	TEST(cnt > 0);
	TheView.Close();

	TheTbl.Close();

	TheTest.Printf(_L("Table B - Write\n"));
	err = TheTbl.Open(TheDb, KTblNameB, RDbRowSet::EReadOnly);
	TEST2(err, KErrNone);
	//The test must fail, because the test app cannot satisfy table B, policy W.
	TRAP(err, TheTbl.InsertL());
	TEST2(err, KErrPermissionDenied);
	err = TheDb.Execute(_L("INSERT INTO B (DATA2) VALUES (45)"));
	TEST2(err, KErrPermissionDenied);

	TheTest.Printf(_L("Table B - Read\n"));
	//The test must pass, because table B has no R policy.
	TRAP(err, res = TheTbl.FirstL());
	TEST2(err, KErrNone);
	TEST(res);
	cnt = TheTbl.CountL();
	TEST(cnt > 0);
	err = TheView.Prepare(TheDb, TDbQuery(_L("SELECT * FROM B")));
	TEST2(err, KErrNone);
	cnt = TheView.CountL();
	TEST(cnt > 0);
	TheView.Close();

	TheTbl.Close();

	TheTest.Printf(_L("Table C - Write\n"));
	err = TheTbl.Open(TheDb, KTblNameC);
	//The test must fail, because the test app cannot satisfy table C, policy W.
	TEST2(err, KErrPermissionDenied);
	err = TheTbl.Open(TheDb, KTblNameC, RDbRowSet::EReadOnly);
	TEST2(err, KErrNone);
	TRAP(err, TheTbl.InsertL());
	TEST2(err, KErrPermissionDenied);
	err = TheDb.Execute(_L("UPDATE C SET DATA1 = 400 WHERE ID < 10"));
	TEST2(err, KErrPermissionDenied);

	TheTest.Printf(_L("Table C - Read\n"));
	//The test must pass, because table C has no R policy.
	TRAP(err, res = TheTbl.FirstL());
	TEST2(err, KErrNone);
	TEST(res);
	cnt = TheTbl.CountL();
	TEST(cnt > 0);
	err = TheView.Prepare(TheDb, TDbQuery(_L("SELECT * FROM C")));
	TEST2(err, KErrNone);
	cnt = TheView.CountL();
	TEST(cnt > 0);
	TheView.Close();

	TheTbl.Close();
	}

static void DoRunL()
	{
	TheTest.Start(_L("An app with \"TABLE A:READ\" capabilities set"));

	TheTest.Next(_L(" @SYMTestCaseID:SYSLIB-DBMS-CT-0015 Open table tests "));
	::TblOpenL();

	TheTest.Next(_L(" @SYMTestCaseID:SYSLIB-DBMS-CT-0016 Table R/W tests "));
	::TblRWL();
	}

TInt E32Main()
    {
	__UHEAP_MARK;
	CTrapCleanup* tc = CTrapCleanup::New();
	TEST(tc != NULL);

	TInt err = TheDbs.Connect();
	TEST2(err, KErrNone);

	TBuf<32> format;
	TheTest.Printf(_L("Open database\n"));
	format.Copy(KSecure);
	format.Append(KSecureDbUid.Name());
	err = TheDb.Open(TheDbs, KDbName, format);
	TEST2(err, KErrNone);

	TRAP(err, ::DoRunL());
	TEST2(err, KErrNone);

	TheView.Close();
	TheTbl.Close();
	TheDb.Close();
	TheDbs.Close();

	TheTest.End();
	TheTest.Close();

	delete tc;

	__UHEAP_MARKEND;
	User::Heap().Check();
	return KErrNone;
    }
