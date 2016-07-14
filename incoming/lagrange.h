/*=============================================================================
	lagrange.h: Lagrange Interporation 
	$Header: /home/boss/ikeda/source/RCS/lagrange.h,v 1.1 1999/11/26 07:49:43 ikeda Exp $
=============================================================================*/
#ifndef	__LAGRANGE_H
#define	__LAGRANGE_H

/*----------------------------------------------------------------------------
	prog  : ikeda@roland.co.jp
	func  : Lagrange Interporation
	date  : Fri Nov 26 16:44:19 JST 1999
	update: 
	entry : n=Data Pair Num,
		xdata=X Data array pointer
		ydata=Y Data array pointer
		x=x
	return: y
	remks :
----------------------------------------------------------------------------*/
extern double lagrange(int n, double* xdata, double* ydata, double x);

#endif	/* __LAGRANGE_H */
/*=============================================================================
	$Log: lagrange.h,v $
	Revision 1.1  1999/11/26 07:49:43  ikeda
	Initial revision

=============================================================================*/
