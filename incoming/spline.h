/*=============================================================================
	spline.h: Spline (4 Point Lagrange Interporation) 
	$Header: /home/boss/ikeda/source/RCS/spline.h,v 1.1 1999/11/26 07:48:55 ikeda Exp $
=============================================================================*/
#ifndef	__SPLINE_H
#define	__SPLINE_H

#include "lagrange.h"

/*----------------------------------------------------------------------------
	prog  : ikeda@roland.co.jp
	func  : Spline (4 Point Lagrrange) Interporation
	date  : Fri Nov 26 16:44:19 JST 1999
	update: 
	entry : n=Data Pair Num,
		xdata=X Data array pointer
		ydata=Y Data array pointer
		x=x
	return: y
	remks :
----------------------------------------------------------------------------*/
extern double spline(int n, double* xdata, double* ydata, double x);

#endif	/* __SPLINE_H */
/*=============================================================================
	$Log: spline.h,v $
	Revision 1.1  1999/11/26 07:48:55  ikeda
	Initial revision

=============================================================================*/
