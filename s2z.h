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
	s2z	S ���ʓ`�B�֐���o���`�ϊ��ɂ�� Z ���ʓ`�B�֐��ɕϊ�����
	
	parameter	a: s���ʓ`�B�֐����q�W���z��		a0+a1s+a2s^2...+aNs^N 
			b: s���ʓ`�B�֐�����W���z��		b0+b1s+b2s^2...+bNs^N
			c: z���ʓ`�B�֐����q�W���i�[�z��	c0+c1z^-1+c2z^-2....+cNz^-N
			d: z���ʓ`�B�֐�����W���i�[�z��	d0+d1z^-1+d2z^-2....+dNz^-N
			N: ����		(0...N) 
			T: �T���v�����O����  1/Fs	
------------------------------------------------------------------------------*/
extern void s2z (const S2Z_TYPE *a, const S2Z_TYPE *b, S2Z_TYPE *c, S2Z_TYPE *d, int N, S2Z_TYPE T);


/*------------------------------------------------------------------------------
	prewarping	�o���`�ϊ����̘c�␳�v�����[�s���O
		
	parameter	wa: �A�i���O�p���g�� (rad/sec) = 2*pi*freq(Hz)
				T: �T���v�����O����  1/Fs	
	return		�␳���ꂽ�p���g�� (rad/sec)
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
