/*==========================================================================
	sres.h: 
	$Author$
	$Revision$
	$Date$
==========================================================================*/
#ifndef	__SRES_H
#define	__SRES_H

/*****  Includes **********************************************************/
#include <math.h>
#include <complex.h>

/*****  External Function's Prototypes  ***********************************/
/*------------------------------------------------------------------------------
	a: s平面伝達関数分子係数配列		a0+a1s+a2s...+aNs 
	b: s平面伝達関数分母係数配列		b0+b1s+b2s...+bNs 
	N: 次数		(0...N) 
	w: 角周波数
------------------------------------------------------------------------------*/
template <class _FLT>
inline complex<_FLT> s2response(_FLT* a, _FLT* b, int N, _FLT w)
{
	double wn = -1.0;
	complex<_FLT> numerator(0, 0), denominator(0, 0);
	for(int k = 0; k <= N; k++) {
		if(k & 1) {
			numerator += *(a+k) * complex<_FLT>(0, wn);
			denominator += *(b+k) * complex<_FLT>(0, wn);
		} else {
			wn *= -1.0;
			numerator += *(a+k) * complex<_FLT>(wn, 0);
			denominator += *(b+k) * complex<_FLT>(wn, 0);
		}
		wn *= w;
	}
	return numerator/denominator;
}

/*-------------------------------------------------------------------------
	Frequency (Hz) -> w 
		freq: Frequency (Hz)
-------------------------------------------------------------------------*/
template <class _FLT>
inline _FLT sFreq2w(_FLT freq)
{
	return 2.0*M_PI*freq;
}

/*-------------------------------------------------------------------------
	w -> Frequency (Hz)
		w: 
-------------------------------------------------------------------------*/
template <class _FLT>
inline _FLT zW2Freq(_FLT w)
{
	return w/2.0/M_PI;
}


#endif	/* __SRES_H */
/*==========================================================================
	$Log$
==========================================================================*/
