/*==============================================================================
	s_trans.c:	1/S Transfer with Frequency, Impedance Scaling for FDNR Filter
		$Header$
==============================================================================*/
#include <stdio.h>
#include <math.h>

double	freq;
double	Cap;
int		curState;
double	val;

#define	PAI	3.141592654

#define	QUIT		0
#define	REGISTER	1
#define	FDNR		2

char	inchar;

int main(argc, argv)
char *argv[];
{
	fputs("Frequency[Hz]: ", stdout);	
	scanf("%lf", &freq);
	fputs("In & Out Cap[F]: ", stdout);	
	scanf("%lf", &Cap);
	fputs("'q':quit, 'r':Register, 'd':FDNR\n", stdout);
	curState = REGISTER;
	printstate();
	while(curState != QUIT) {
		switch(getc(stdin)) {
			case	'q':
			case	'Q':
				curState = QUIT;
				break;
			case	'r':
			case	'R':
				curState = REGISTER;
				continue;
				break;
			case	'd':
			case	'D':
				curState = FDNR;
				continue;
				break;
			case 	'\n':
				break;
			default:
				ungetc(stdin);
		}
		printstate();
		switch(curState) {
			case	REGISTER:
				scanf("%le", &val);
				printf("%lf\n", val/Cap/freq/2.0/PAI);
				break;
			case	FDNR:
				scanf("%lf", &val);
				printf("%le\n", val*Cap/freq/2.0/PAI);
				break;
		}
	}
}

printstate()
{
	switch(curState) {
		case	REGISTER:
			fputs("R:", stdout);
			break;
		case	FDNR:
			fputs("D elem:", stdout);
				break;
	}
		
}

