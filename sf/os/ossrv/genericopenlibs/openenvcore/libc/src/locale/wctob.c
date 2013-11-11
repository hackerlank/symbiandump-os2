/*-
 * 
 * Copyright (c) 2002-2004 Tim J. Robbins.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * * Portions Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies). All rights reserved. 
 */

#include <sys/cdefs.h>
__FBSDID("$FreeBSD: src/lib/libc/locale/wctob.c,v 1.4 2004/05/12 14:26:54 tjr Exp $");

#include <limits.h>
#include <stdio.h>
#include <wchar.h>
#ifndef __SYMBIAN32__
#include "mblocal.h"
#endif //__SYMBIAN32__

EXPORT_C int
wctob(wint_t c)
{
	static const mbstate_t initial = {0,{0}};
	mbstate_t mbs = initial;
	char buf[MB_LEN_MAX];
	
#ifndef __SYMBIAN32__
	if (c == WEOF || __wcrtomb(buf, c, &mbs) != 1)
#else //__SYMBIAN32__
	if (c == WEOF || wcrtomb(buf, c, &mbs) != 1)
#endif //__SYMBIAN32__
		return (EOF);
	return ((unsigned char)*buf);
}