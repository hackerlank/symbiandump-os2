/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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


// [INCLUDE FILES] - do not remove
#include <e32svr.h>
#include <StifParser.h>
#include <Stiftestinterface.h>
#include "BCNoNamespace.h"

//headers exported from No namespace headers API
#include <ios>
#include <streambuf.h>
#include <strstream.h>
#include <locale>
#include <iomanip.h>
#include <sstream>
#include <fstream.h>
#include <iostream.h>
#include <iomanip>
#include <cstring>
#include <iostream>
#include <ostream.h>
#include <streambuf>
#include <ostream>
#include <iosfwd>
#include <istream>
#include <fstream>
#include <strstream>

// EXTERNAL DATA STRUCTURES
//extern  ?external_data;

// EXTERNAL FUNCTION PROTOTYPES  
//extern ?external_function( ?arg_type,?arg_type );

// CONSTANTS
//const ?type ?constant_var = ?constant;

// MACROS
//#define ?macro ?macro_def

// LOCAL CONSTANTS AND MACROS
//const ?type ?constant_var = ?constant;
//#define ?macro_name ?macro_def

// MODULE DATA STRUCTURES
//enum ?declaration
//typedef ?declaration

// LOCAL FUNCTION PROTOTYPES
//?type ?function_name( ?arg_type, ?arg_type );

// FORWARD DECLARATIONS
//class ?FORWARD_CLASSNAME;

// ============================= LOCAL FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// ?function_name ?description.
// ?description
// Returns: ?value_1: ?description
//          ?value_n: ?description_line1
//                    ?description_line2
// -----------------------------------------------------------------------------
//
/*
?type ?function_name(
    ?arg_type arg,  // ?description
    ?arg_type arg)  // ?description
    {

    ?code  // ?comment

    // ?comment
    ?code
    }
*/

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CBCNoNamespace::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CBCNoNamespace::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CBCNoNamespace::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CBCNoNamespace::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestAPI", CBCNoNamespace::TestAPI ),
        //ADD NEW ENTRY HERE
        // [test cases entries] - Do not remove

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CBCNoNamespace::TestAPI
// TestAPI test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CBCNoNamespace::TestAPI( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( KBCNoNamespace, "BCNoNamespace" );
    _LIT( KTestAPI, "In TestAPI" );
    TestModuleIf().Printf( 0, KBCNoNamespace, KTestAPI );
    // Print to log file
    iLog->Log( KTestAPI );

		_LIT( KResult, "No functions to be tested");
		_LIT( KComment, "No Namespace headers API has passed");
    TestModuleIf().Printf( 0, KResult, KComment);

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CBCNoNamespace::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
/*
TInt CBCNoNamespace::?member_function(
   CItemParser& aItem )
   {

   ?code

   }
*/

// ========================== OTHER EXPORTED FUNCTIONS =========================
// None

//  [End of File] - Do not remove
