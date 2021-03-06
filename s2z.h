/*==============================================================================
	s2z.h: S -> Z Bi-linear transfer
    		Please refer http://web.boss.rosenet/~ikeda/techdoc/bilinear.pdf
		$Header: /home/boss/ikeda/source/RCS/s2z.h,v 1.1 2004/12/22 00:51:25 ikeda Exp ikeda $
==============================================================================*/	
#ifndef	__S2Z_H
#define	__S2Z_H


#define	S2Z_TYPE	double		// or float

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */
/*------------------------------------------------------------------------------
	s2z	S 平面伝達関数を双線形変換により Z 平面伝達関数に変換する
	
	parameter	a: s平面伝達関数分子係数配列		a0+a1s+a2s^2...+aNs^N 
			b: s平面伝達関数分母係数配列		b0+b1s+b2s^2...+bNs^N
			c: z平面伝達関数分子係数格納配列	c0+c1z^-1+c2z^-2....+cNz^-N
			d: z平面伝達関数分母係数格納配列	d0+d1z^-1+d2z^-2....+dNz^-N
			N: 次数		(0...N) 
			T: サンプリング周期  1/Fs	
------------------------------------------------------------------------------*/
extern void s2z (const S2Z_TYPE *a, const S2Z_TYPE *b, S2Z_TYPE *c, S2Z_TYPE *d, int N, S2Z_TYPE T);


/*------------------------------------------------------------------------------
	prewarping	双線形変換時の歪補正プリワーピング
		
	parameter	wa: アナログ角周波数 (rad/sec) = 2*pi*freq(Hz)
				T: サンプリング周期  1/Fs	
	return		補正された角周波数 (rad/sec)
------------------------------------------------------------------------------*/
extern S2Z_TYPE s2zPrewarping(S2Z_TYPE wa, S2Z_TYPE T);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* __S2Z_H */
/*==============================================================================
	$Log: s2z.h,v $
	Revision 1.1  2004/12/22 00:51:25  ikeda
	Initial revision

	Revision 1.1  2004/12/22 00:29:20  ikeda
	Initial revision

 * Revision 1.1  98/03/20 16:41:26  ikeda
 * Initial revision
 * 
==============================================================================*/	
