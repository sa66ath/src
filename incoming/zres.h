/*==========================================================================
	zres.h: 
	$Author$
	$Revision$
	$Date$
==========================================================================*/
#ifndef	__ZRES_H
#define	__ZRES_H

/*****  Includes **********************************************************/
#include <math.h>
#include <complex.h>

/*****  External Function's Prototypes  ***********************************/
/*-------------------------------------------------------------------------
	a: z平面伝達関数分子係数配列		a0+a1s+a2s...+aNs 
	b: z平面伝達関数分母係数配列		b0+b1s+b2s...+bNs 
	N: 次数		(0...N) 
	w: 角周波数
-------------------------------------------------------------------------*/
template <class _FLT>
complex<_FLT> z2response(_FLT* a, _FLT* b, int N, _FLT w);

/*-------------------------------------------------------------------------
	Frequency (Hz) -> w 
		freq: Frequency (Hz)
		fs:   Sampling Frequency (Hz)
-------------------------------------------------------------------------*/
template <class _FLT>
inline _FLT zFreq2w(_FLT freq, _FLT fs)
{
	return 2.0*M_PI*freq/fs;
}

/*-------------------------------------------------------------------------
	w -> Frequency (Hz)
		w: 
		fs:   Sampling Frequency (Hz)
-------------------------------------------------------------------------*/
template <class _FLT>
inline _FLT zW2Freq(_FLT w, _FLT fs)
{
	return w*fs/2.0/M_PI;
}


#endif	/* __ZRES_H */
/*==========================================================================
	$Log$
==========================================================================*/