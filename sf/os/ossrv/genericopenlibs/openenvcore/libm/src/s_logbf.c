/*--------------------------------------------------------------------
 *� Portions copyright (c) 2006 Nokia Corporation.  All rights reserved.
 *--------------------------------------------------------------------
*/
/* s_logbf.c -- float version of s_logb.c.
 * Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.
 */

/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */
#ifndef __SYMBIAN32__
#ifndef lint
static char rcsid[] = "$FreeBSD: src/lib/msun/src/s_logbf.c,v 1.7 2002/05/28 18:15:04 alfred Exp $";
#endif
#endif //__SYMBIAN32__

#include <math.h>
#include "math_private.h"

EXPORT_C float
logbf(float x)
{
	int32_t ix;
	GET_FLOAT_WORD(ix,x);
	ix &= 0x7fffffff;			/* high |x| */
	if(ix==0) return (float)-1.0/fabsf(x);
	if(ix>=0x7f800000) return x*x;
	if((ix>>=23)==0) 			/* IEEE 754 logb */
		return -126.0;
	else
		return (float) (ix-127);
}
