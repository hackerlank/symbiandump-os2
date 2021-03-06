/*-
 * � Portions copyright (c) 2006 Nokia Corporation.  All rights reserved.
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "@(#)err.c	8.1 (Berkeley) 6/4/93";
#endif /* LIBC_SCCS and not lint */
#include <sys/cdefs.h>
__FBSDID("$FreeBSD: src/lib/libc/gen/err.c,v 1.13 2002/03/29 22:43:41 markm Exp $");

#include "namespace.h"
#include <err.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "un-namespace.h"

#include "libc_private.h"

#if (defined(__SYMBIAN32__) && (defined(__WINSCW__) || defined(__WINS__)))
#include "libc_wsd_defs.h"
#endif

#ifndef EMULATOR

static FILE *err_file; /* file to use for error output */

#ifdef __SYMBIAN_COMPILE_UNUSED__
static void (*err_exit)(int);
#endif

#else //EMULATOR

GET_STATIC_VAR_FROM_TLS(err_file, FILE *)

#define err_file (*GET_WSD_VAR_NAME(err_file, s)())

#ifdef __SYMBIAN_COMPILE_UNUSED__
#define err_exit (GetGlobals()->_s_err_exit)
#endif

#endif //EMULATOR

/*
 * This is declared to take a `void *' so that the caller is not required
 * to include <stdio.h> first.  However, it is really a `FILE *', and the
 * manual page documents it as such.
 */
void
err_set_file(void *fp)
{
	if (fp)
		err_file = fp;
	else
		err_file = stderr;
}

#ifdef __SYMBIAN_COMPILE_UNUSED__

void
err_set_exit(void (*ef)(int))
{
	err_exit = ef;
}

#ifdef __SYMBIAN32__
#define err _err
#else
__weak_reference(_err, err);
#endif //__SYMBIAN32__

void
_err(int eval, const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	verrc(eval, errno, fmt, ap);
	va_end(ap);
}

void
verr(eval, fmt, ap)
	int eval;
	const char *fmt;
	va_list ap;
{
	verrc(eval, errno, fmt, ap);
}

void
errc(int eval, int code, const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	verrc(eval, code, fmt, ap);
	va_end(ap);
}

void
verrc(eval, code, fmt, ap)
	int eval;
	int code;
	const char *fmt;
	va_list ap;
{
	if (err_file == 0)
		err_set_file((FILE *)0);
	fprintf(err_file, "%s: ", _getprogname());
	if (fmt != NULL) {
		vfprintf(err_file, fmt, ap);
		fprintf(err_file, ": ");
	}
	fprintf(err_file, "%s\n", strerror(code));
	if (err_exit)
		err_exit(eval);
	exit(eval);
}

void
errx(int eval, const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	verrx(eval, fmt, ap);
	va_end(ap);
}

void
verrx(eval, fmt, ap)
	int eval;
	const char *fmt;
	va_list ap;
{
	if (err_file == 0)
		err_set_file((FILE *)0);
	fprintf(err_file, "%s: ", _getprogname());
	if (fmt != NULL)
		vfprintf(err_file, fmt, ap);
	fprintf(err_file, "\n");
	if (err_exit)
		err_exit(eval);
	exit(eval);
}

#ifdef __SYMBIAN32__
#define warn _warn
#else
__weak_reference(_warn, warn);
#endif //__SYMBIAN32__

void
_warn(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vwarnc(errno, fmt, ap);
	va_end(ap);
}

void
vwarn(fmt, ap)
	const char *fmt;
	va_list ap;
{
	vwarnc(errno, fmt, ap);
}

void
warnc(int code, const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vwarnc(code, fmt, ap);
	va_end(ap);
}

void
vwarnc(code, fmt, ap)
	int code;
	const char *fmt;
	va_list ap;
{
	if (err_file == 0)
		err_set_file((FILE *)0);
	fprintf(err_file, "%s: ", _getprogname());
	if (fmt != NULL) {
		vfprintf(err_file, fmt, ap);
		fprintf(err_file, ": ");
	}
	fprintf(err_file, "%s\n", strerror(code));
}

#endif

void
warnx(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vwarnx(fmt, ap);
	va_end(ap);
}

void
vwarnx(fmt, ap)
	const char *fmt;
	va_list ap;
{
	if (err_file == 0)
		err_set_file((FILE *)0);
	fprintf(err_file, "%s: ", _getprogname());
	if (fmt != NULL)
		vfprintf(err_file, fmt, ap);
	fprintf(err_file, "\n");
}
