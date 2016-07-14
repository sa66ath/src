/*==========================================================================
	sres.cpp: 
	$Author$
	$Revision$
	$Date$
==========================================================================*/
#define	M_DEBUG
/*****  Includes **********************************************************/
#include <math.h>
#include <complex.h>

#include "sres.h"

#ifdef	M_DEBUG
#include <iostream.h>
#endif	/* M_DEBUG */

/**************************************************************************/
/*------------------------------------------------------------------------------
	For Module Debug
------------------------------------------------------------------------------*/
#ifdef	M_DEBUG
main()
{
	int dim;
	
	cout << "Dimension=";
	cin >> dim;
	double* a = new double[dim+1];
	double* b = new double[dim+1];

	for(int i = 0; i <= dim; i++) {
		cout << "a" << i << "= ";
		cin >> *(a+i);
	}
	
	for(int i = 0; i <= dim; i++) {
		cout << "b" << i << "= ";
		cin >> *(b+i);
	}

	for(double freq = 10.0; freq < 20000.0; freq *= pow(2.0, 1.0/6.0)) {
		complex<double> r = s2response(a, b, dim, sFreq2w(freq)); 
		cout << "freq=" << freq << "(Hz) " 
			<< "amp=" << 20.0*log10(abs(r)) << "(dB)" 
			<< "  phase=" << 180.0/M_PI*arg(r) << endl;
	}
}
#endif	/* M_DEBUG */

/*==========================================================================
	$Log$
==========================================================================*/
