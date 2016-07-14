/*=============================================================================
	bquad2.c: Determine digital 2nd demension Bi-quad filter coefficients
								S.Ikeda 28th,Nov,1991
=============================================================================*/
#include <stdio.h>
#include <math.h>
#include <signal.h>

#define	PAI 3.141592654
#define	LPF	0
#define	HPF	1

double	prewarping();
void	error();

char *progn;
double	a0, a1, a2, b1, b2;
double	Q  = 0.7071067812;		/* 1.0/sqr(2.0) */
double	fs = 48000.0;		
double	fc = 0.0;
int		ftype = LPF;

/*-----------------------------------------------------------------------------
	main		return  0: program normal end	-1: abnormal end
-----------------------------------------------------------------------------*/
main(argc, argv)
char *argv[];
{
	double T, A, B, C, D, E;
	double Oc;
	int	c;

	signal(SIGFPE, error);
	progn = argv[0];
	fprintf(stderr,"*** Determine Bi-quad Digital filter coefficients ***\n\n");
	while(1) {
		fprintf(stderr, "Filter type(0:LPF 1:HPF)[%s] = ",
								(LPF == ftype)? "LPF":"HPF");
		if('\n' != (c = getchar())) {
			ungetc(c, stdin);
			scanf("%d%*c", &ftype);
		}
		fprintf(stderr, "Sampling freq.[%5.0lf]  (Hz) = ", fs);
		if('\n' != (c = getchar())) {
			ungetc(c, stdin);
			scanf("%lf%*c", &fs);
		}
		T = 1.0/fs;
		if(0.0 == fc) {
			fprintf(stderr, "Cut off freq.          (Hz) = ");
			scanf("%lf%*c", &fc);
		} else {
			fprintf(stderr, "Cut off freq. [%7.1lf](Hz) = ", fc);
			if('\n' != (c = getchar())) {
				ungetc(c, stdin);
				scanf("%lf%*c", &fc);
			}
		}
		fprintf(stderr, "Quality factor[%8lf]    = ", Q);
		if('\n' != (c = getchar())) {
			ungetc(c, stdin);
			scanf("%lf%*c", &Q);
		}

		Oc = prewarping(2.0*PAI*fc, T);

		if(LPF == ftype) 	lpf2(Oc, Q, &A, &B, &C, &D, &E);
		else				hpf2(Oc, Q, &A, &B, &C, &D, &E);

#if	DEBUG
		fprintf(stderr, "Oc=%lf, A=%lf, B=%lf, C=%lf, D=%lf, E=%lf\n",
				Oc,		A,		B,		C,		D,	E);
#endif   /* DEBUG */

		s2z(T, A, B, C, D, E);

		output();

		fprintf(stderr, "\nContinue? (y or n)");
		if('n' == getchar())	break;
		getchar();
		fprintf(stderr, "\n");
	}
	return 0;
}

/*-----------------------------------------------------------------------------
	lpf2
-----------------------------------------------------------------------------*/
lpf2(Oc, Q, A, B, C, D, E)
double	Oc, Q;
double	*A, *B, *C, *D, *E;
{
	*A = Oc*(1.0/Q);
	*B = Oc*Oc;
	*C = 0.0;
	*D = 0.0;
	*E = Oc*Oc;
}

/*---------------------------------------------------------------------------
	hpf2
---------------------------------------------------------------------------*/
hpf2(Oc, Q, A, B, C, D, E)
double	Oc, Q;
double	*A, *B, *C, *D, *E;
{
	*A = (1.0/Q)*Oc;
	*B = Oc*Oc;
	*C = 1.0;
	*D = 0.0;
	*E = 0.0;
}

/*--------------------------------------------------------------------------
	s2z		transter to z from s
--------------------------------------------------------------------------*/
s2z(T, A, B, C, D, E)
double T, A, B, C, D, E;
{
	double alpha, G, beta;
	
	alpha = 2.0/T;
	G = 1.0/(alpha*alpha + A*alpha + B);
	beta = C*alpha*alpha;
	
	a2 = G*(beta - D*alpha + E);
	a1 = G*(2.0 * (E - beta));
	a0 = a2;

	b1 = 2.0*G*(B - alpha*alpha);
	b2 = G*(alpha*alpha - A*alpha + B);
}

/*----------------------------------------------------------------------------
	prewarping		return value: Analog filter cut off
----------------------------------------------------------------------------*/
double prewarping(wc, T)
double	wc;			/* Digital filter cut off (RADIAN/sec) */
double  T;			/* Sampling frequency */
{
	return 	2.0/T * tan(wc*T/2.0);
}

/*---------------------------------------------------------------------------
	output
---------------------------------------------------------------------------*/
output()
{
	printf("\n*** %s: fc=%7.1lf, Q=%8lf, fs=%5.0lf ***\n",
			(LPF == ftype)? "LPF":"HPF", fc, Q, fs); 
	printf("a0 = % lf\n", a0);
	printf("a1 = % lf		b1 = % lf\n", a1, -1.0 * b1);
	printf("a2 = % lf		b2 = % lf\n", a2, -1.0 * b2);

	return 0;
}
/*---------------------------------------------------------------------------
	error
---------------------------------------------------------------------------*/
void error()
{
	fprintf(stderr, "%s: ERROR %s\n", progn, "arithmetic exception");
	exit(-1);
}
