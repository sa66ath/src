/*------------------------------------------------------------------------------
 	vr360.c: 360度VR の絶対値を求める
			May 29th 2012
			Shoichi Ikeda	BOSS Corporation
			ikeda@roland.co.jp

	プログラミング・モデル提示の為に浮動小数点演算にしているが、
	実際にはドンくさい小数点など使わずに、整数化して実装すべし。
------------------------------------------------------------------------------*/

/*
 * 	param:	valA = value of A (0.0 <= valA < 1.0)
 * 		valB = value of B (0.0 <= valB < 1.0) 
 *
 * 	return:	0.0(0 deg) - 1.0(180 deg) - 2.0(360 deg)
 */
#include <math.h>	/* for fabs() */

double GetAngle(double valA, double valB)
{
	double angle;

	double diffA, diffB, coefA, coefB;

	diffA = fabs(valA-0.5);
	diffB = fabs(valB-0.5);

	if(diffA < diffB) {
		coefA = 1.0 - 2.0*diffA;
		coefB = 1.0 - coefA;
	} else {
		coefB = 1.0 - 2.0*diffB;
		coefA = 1.0 - coefB;	
	}
	angle = coefA*((valB < 0.5)? valA:2.0-valA) +
		coefB*((valA < 0.5)? (((valB <= 0.5)? 0.5:2.5)-valB):0.5+valB);

	return angle;
}



/*******************************************************************************/
/* #define	MODULE_DEBUG */

#ifdef	MODULE_DEBUG
#include <stdio.h>

int main(int argc, char* argv[])
{
	double	a, b;

	while(scanf("%lf %lf", &a, &b)) {
		printf("\t\tangle = %lf\n", GetAngle(a, b));
	}
	return 0;
}

#endif	/* MODULE_DEBUG */
