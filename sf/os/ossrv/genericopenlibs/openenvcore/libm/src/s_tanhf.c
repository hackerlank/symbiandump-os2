/*--------------------------------------------------------------------
 *� Portions copyright (c) 2006 Nokia Corporation.  All rights reserved.
 *--------------------------------------------------------------------
*/
/* s_tanhf.c -- float version of s_tanh.c.
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
static char rcsid[] = "$FreeBSD: src/lib/msun/src/s_tanhf.c,v 1.7 2002/05/28 18:15:04 alfred Exp $";
#endif
#endif //__SYMBIAN32__

#include <math.h>
#include "math_private.h"

static const float one=1.0, two=2.0, tiny = 1.0e-30;

EXPORT_C float
tanhf(float x)
{
	float t,z;
	int32_t jx,ix;

	GET_FLOAT_WORD(jx,x);
	ix = jx&0x7fffffff;

    /* x is INF or NaN */
	if(ix>=0x7f800000) {
	    if (jx>=0) return one/x+one;    /* tanh(+-inf)=+-1 */
	    else       return one/x-one;    /* tanh(NaN) = NaN */
	}

    /* |x| < 22 */
	if (ix < 0x41b00000) {		/* |x|<22 */
	    if (ix<0x24000000) 		/* |x|<2**-55 */
		return x*(one+x);    	/* tanh(small) = small */
	    if (ix>=0x3f800000) {	/* |x|>=1  */
		t = expm1f(two*fabsf(x));
		z = one - two/(t+two);
	    } else {
	        t = expm1f(-two*fabsf(x));
	        z= -t/(t+two);
	    }
    /* |x| > 22, return +-1 */
	} else {
	    z = one - tiny;		/* raised inexact flag */
	}
	return (jx>=0)? z: -z;
}
