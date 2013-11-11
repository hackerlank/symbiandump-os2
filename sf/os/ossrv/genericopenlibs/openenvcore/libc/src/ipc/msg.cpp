/*
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
* Description:  Implementation of message queue (POSIX Standard).
*
*/


// INCLUDE FILES
#include <errno.h>
#include <sys/msg.h>
#include <unistd.h>
#include "sysreent.h"

// -----------------------------------------------------------------------------
// Funcation name: msgget
// Description: Get the message queue identifier using the IPC key generated by ftok.
// Returns: None zero number (message queue identifier): On success
//          -1              : On error.
// In case of error, errno value set to
//          EACCESS - Message queue exists but access denied.
//          EEXIST - Message queue identifier exists for the argument key
//                   but ((msgflg & IPC_CREAT) && (msgflg & IPC_EXCL)) is non-zero
//          ENOENT - Message queue identifier does not exist for the argument key
//                   and (msgflg & IPC_CREAT) is 0
//          ENOSPC - Message queue identifier is to be created but the system-imposed
//                   limit on the maximum number of allowed message queue identifiers
//                   system-wide would be exceeded
// -----------------------------------------------------------------------------
//

extern "C" {
EXPORT_C int msgget(key_t key, int msgflg)
    {
    return _msgget_r(key, msgflg, &errno);
    }

// -----------------------------------------------------------------------------
// Funcation name: msgsnd
// Description: Used to send a message to the queue associated with the message
//              identifier specified by msqid.
// Returns: 0    : On success
//          -1   : On error.
// In case of error, errno value set to
//          EACCESS - Operation permission is denied to the calling process.
//          EAGAIN - The message cannot be sent for one of the reasons cited
//                   above and (msgflg & IPC_NOWAIT) is non-zero.
//          EIDRM - The message queue identifier msqid is removed from the system.
//          EINTR - The msgsnd() function was interrupted by a signal.
//          EINVAL - The value of msqid is not a valid message queue identifier,
//                   or the value of mtype is less than 1; or the value of msgsz
//                   is less than 0 or greater than the system-imposed limit
// -----------------------------------------------------------------------------
//
EXPORT_C int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg)
    {
    return _msgsnd_r(msqid, msgp, msgsz, msgflg, &errno);
    }

// -----------------------------------------------------------------------------
// Funcation name: msgrcv
// Description: Reads a message from the queue associated with the message queue identifier.
// Returns: Number of bytes copied within the received buffer : On success
//          -1   : On error.
// In case of error, errno value set to
//          EACCESS - Operation permission is denied to the calling process.
//          E2BIG � Length of the sessage is greater than msgsz and (msgflg & MSG_NOERROR) is 0.
//          EIDRM - The message queue identifier msqid is removed from the system.
//          EINTR - The msgrcv() function was interrupted by a signal.
//          EINVAL - msqid is not a valid message queue identifier.
//          ENOMSG - The queue does not contain a message of the desired type and
//                   (msgflg & IPC_NOWAIT) is non-zero.
// -----------------------------------------------------------------------------
//
EXPORT_C ssize_t msgrcv(int msqid, void* msgp, size_t msgsz, long msgtyp, int msgflg)
    {
    return _msgrcv_r(msqid, msgp, msgsz, msgtyp, msgflg, &errno);
    }

// -----------------------------------------------------------------------------
// Funcation name: msgctl
// Description: Provides an interface to control message queue and control
//              operations as specified by cmd.
// Returns: 0  : On success
//          -1 : On error.
// In case of error, errno value set to
//          EACCESS - The argument cmd is IPC_STAT and the calling process does
//                    not have read permission, see IPC.
//          EINVAL � The value of msqid is not a valid message queue identifier;
//                   or the value of cmd is not a valid command.
//          EPERM -  The argument cmd is IPC_RMID or IPC_SET and the effective
//                   user ID of the calling process is not equal to that of a
//                   process with appropriate privileges and it is not equal to
//                   the value of msg_perm.cuid or msg_perm.uid in the data
//                   structure associated with msqid.
//          EPERM -  The argument cmd is IPC_SET, an attempt is being made to
//                   increase to the value of msg_qbytes, and the effective user
//                   ID of the calling process does not have appropriate privileges
// -----------------------------------------------------------------------------
//
EXPORT_C int msgctl(int msqid, int cmd, struct msqid_ds* buf)
    {
    return _msgctl_r(msqid, cmd, buf, &errno);
    }

} // extern "C" {

//  End of File