@rem
@rem Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
@rem All rights reserved.
@rem This component and the accompanying materials are made available
@rem under the terms of "Eclipse Public License v1.0"
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

md c:\logs\
attrib -r c:\logs\comsdbg.ini
copy c:\logs\comsdbg.ini c:\logs\comsdbg.ini.old
copy z:\TestData\Scripts\ts_comsdbg_file.ini c:\logs\ts_flogger.ini
attrib -r c:\logs\ts_flogger.ini
