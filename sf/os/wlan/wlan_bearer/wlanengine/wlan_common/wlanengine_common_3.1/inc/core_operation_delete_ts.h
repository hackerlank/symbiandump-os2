/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Statemachine for deleting a traffic stream.
*
*/

/*
* %version: 3 %
*/

#ifndef CORE_OPERATION_DELETE_TS_H
#define CORE_OPERATION_DELETE_TS_H

#include "core_operation_base.h"
#include "abs_core_frame_handler.h"

/**
 * Statemachine for deleting a traffic stream.
 *
 * @lib wlmserversrv.lib
 * @since S60 v3.1
 */
NONSHARABLE_CLASS( core_operation_delete_ts_c ) :
    public core_operation_base_c
    {

public:

    enum core_state_e
        {
        core_state_init = core_base_state_next,
        core_base_state_parameters_set,
        core_state_MAX
        };

    core_operation_delete_ts_c(
        u32_t request_id,
        core_server_c* server,
        abs_core_driverif_c* drivers,
        abs_core_server_callback_c* adaptation,
        u32_t stream_id );

    virtual ~core_operation_delete_ts_c();

protected:

    /**
     * This method is called when a pending request has been completed
     * and so sub-operations are pending.
     *
     * @since S60 v3.1
     * @return status of the operation:
     *     core_error_request_pending if the operation is not finished,
     *     otherwise the status code of the finished operation
     */
    core_error_e next_state();

private: // data

    /**
     * The ID of the traffic stream.
     */
    u32_t id_m;

    };

#endif // CORE_OPERATION_DELETE_TS_H
