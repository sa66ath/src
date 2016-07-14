#include <stdio.h>
#include <math.h>
#include <limits.h>

#define	MAX_DIM	100

double	coef[MAX_DIM];
double	pi = 3.14;
double	bottom = 20;
double	top = 20000;
int	devide = 128;
double	T = 1.0/44100.0;

main()
{
	input();
	calc();
}


input()
{
	int	i;
	int	val;

	for(i = 0; (EOF != scanf("%x", &val)) && i < MAX_DIM; i++) {
		val <<= 16;
		coef[i] = val/(double)INT_MAX;
	}
}

calc()
{
	double	ex;
	int	i;
	double	freq;
	double	real = 0.0, image = 0.0;
	double	gain;

	ex = log10(top/bottom)/devide;
	for(freq = bottom; freq <= top; freq *= pow(10.0, ex)) {
		real = image = 0.0;
		for(i = MAX_DIM - 1; i >= 0; i--) {
			real += coef[i]*cos((double)i*2.0*3.14*freq*T);
			image += coef[i]*sin((double)i*2.0*3.14*freq*T);
		}
		gain = sqrt(real*real + image*image);
		printf("%20lf	%lf\n", freq, 20.0*log10(gain));
	}
}

