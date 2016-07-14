/*==========================================================================
	zres.cpp: 
	$Author$
	$Revision$
	$Date$
==========================================================================*/
/*****  Includes **********************************************************/
#include <math.h>
#include <complex.h>

#include "zres.h"

#ifdef	M_DEBUG
#include <iostream.h>
#endif	/* M_DEBUG */

/**************************************************************************/
/*------------------------------------------------------------------------------
	a: z平面伝達関数分子係数配列		a0+a1s+a2s...+aNs 
	b: z平面伝達関数分母係数配列		b0+b1s+b2s...+bNs 
	N: 次数		(0...N) 
	w: 角周波数
------------------------------------------------------------------------------*/
template <class _FLT>
complex<_FLT> z2response(_FLT* a, _FLT* b, int N, _FLT w)
{
	int k;
	complex<_FLT> numerator(0, 0), denominator(0, 0);

	for(k = 0; k <= N; k++) {
		numerator += *(a+k) * complex<_FLT>(cos((N-k)*w), sin((N-k)*w));	
		denominator += *(b+k) * complex<_FLT>(cos((N-k)*w), sin((N-k)*w));	
	}

	return numerator/denominator;
}


/*------------------------------------------------------------------------------
	For Module Debug
------------------------------------------------------------------------------*/
#ifdef	M_DEBUG
main()
{
	double Fs = 44100.0;
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
		double w = 2*M_PI*freq/Fs;
		complex<double> r = z2response(a, b, dim, w); 
		cout << "freq=" << freq << "(Hz) " 
			<< "amp=" << 20.0*log10(abs(r)) << "(dB)" 
			<< "  phase=" << 180.0/M_PI*arg(r) << endl;
	}
}
#endif	/* M_DEBUG */

/*==========================================================================
	$Log$
==========================================================================*/
