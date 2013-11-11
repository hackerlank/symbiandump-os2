@rem
@rem Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
@rem All rights reserved.
@rem This component and the accompanying materials are made available
@rem under the terms of the License "Eclipse Public License v1.0"
@rem which accompanies this distribution, and is available
@rem at the URL "http://www.eclipse.org/legal/epl-v10.html".
@rem
@rem Initial Contributors:
@rem Nokia Corporation - initial contribution.
@rem
@rem Contributors:
@rem
@rem Description: 
@rem

rem Compilations needed in order to compile asnpkcs product code
rem ============================================================

rem asnpkcs product code depends only on code residing in the cbr
rem No additional compilations required

call cd %SECURITYSOURCEDIR%\asnpkcs\group
call bldmake bldfiles 
call abld build winscw udeb

 


 