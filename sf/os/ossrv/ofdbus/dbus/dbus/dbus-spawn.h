/* -*- mode: C; c-file-style: "gnu" -*- */
/* dbus-spawn.h Wrapper around fork/exec
 * 
 * Copyright (C) 2002, 2003  Red Hat, Inc.
 * Copyright (C) 2003 CodeFactory AB
 * Portion Copyright � 2008 Nokia Corporation and/or its subsidiary(-ies). All rights reserved.
 * Licensed under the Academic Free License version 2.1
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#ifndef DBUS_SPAWN_H
#define DBUS_SPAWN_H

#ifdef __SYMBIAN32__
//these are not system headers in build time
#include "dbus-string.h"
#include <dbus/dbus-errors.h>
#include "dbus-watch.h"
#else
#include <dbus/dbus-string.h>
#include <dbus/dbus-errors.h>
#include <dbus/dbus-watch.h>
#endif

DBUS_BEGIN_DECLS

typedef void (* DBusSpawnChildSetupFunc) (void *user_data);

typedef struct DBusBabysitter DBusBabysitter;

#ifdef __SYMBIAN32__
IMPORT_C
#endif
dbus_bool_t _dbus_spawn_async_with_babysitter     (DBusBabysitter           **sitter_p,
                                                   char                     **argv,
                                                   DBusSpawnChildSetupFunc    child_setup,
                                                   void                      *user_data,
                                                   DBusError                 *error);
#ifdef __SYMBIAN32__
IMPORT_C
#endif
DBusBabysitter* _dbus_babysitter_ref              (DBusBabysitter            *sitter);
#ifdef __SYMBIAN32__
IMPORT_C
#endif
void        _dbus_babysitter_unref                (DBusBabysitter            *sitter);
#ifdef __SYMBIAN32__
IMPORT_C
#endif
void        _dbus_babysitter_kill_child           (DBusBabysitter            *sitter);
#ifdef __SYMBIAN32__
IMPORT_C
#endif
dbus_bool_t _dbus_babysitter_get_child_exited     (DBusBabysitter            *sitter);
#ifdef __SYMBIAN32__
IMPORT_C
#endif
void        _dbus_babysitter_set_child_exit_error (DBusBabysitter            *sitter,
                                                   DBusError                 *error);
#ifdef __SYMBIAN32__
IMPORT_C
#endif
dbus_bool_t _dbus_babysitter_set_watch_functions  (DBusBabysitter            *sitter,
                                                   DBusAddWatchFunction       add_function,
                                                   DBusRemoveWatchFunction    remove_function,
                                                   DBusWatchToggledFunction   toggled_function,
                                                   void                      *data,
                                                   DBusFreeFunction           free_data_function);

DBUS_END_DECLS

#endif /* DBUS_SPAWN_H */
