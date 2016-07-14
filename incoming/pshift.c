#include <stdio.h>
#include <math.h>

main()
{
	double	a, Ratio;
	int shift;
	int	ha;	

	for(shift = -24; shift <= 24; shift++) {
		Ratio = pow(2.0, (double)shift/12.0); 
		a = 1.0/Ratio - 1.0;
		ha = a*128.0*256.0; 
		printf("%+3d, %lf, %lf:0x%04x\n", shift, Ratio, a, 0xfffe & ha);
	}
}
