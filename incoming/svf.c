#include <stdio.h>
#include <math.h>

#define	Fs	44100.0
#define	PI	3.1415926539
#define	PI2	(double)(2.0*PI)

typedef	struct {
	double	Fc;
	double	Qc;
} SVFCoef;


SVFCoef getcoef(fo, fs, Qa)
double	fo, fs, Qa;
{
	SVFCoef	res;
	double	A, q, p, m, x, d2, d1, Fc, Qc;

	A = cos(PI2*fo/fs);
	q = Qa;
	p = 1 - q*q;
	if(p != 0.0) {
		m = 2.0/p*(A*(A+p-1.0) - (A-1.0)*sqrt(A*A+2.0*p*A+p));
	} else {
		m = (A+1.0)/A;
	}
	x = (m - sqrt(m*m - 4.0))/2.0;
	d2 = x*x;
	d1 = -2.0*A*x;

	res.Fc = sqrt(1.0+d1+d2);
	res.Qc = (1.0 - d2)/Fc;
	return res;
}

char *notename[12] = {
	"C ",
	"C#",
	"D ",
	"D#",
	"E ",
	"F ",
	"F#",
	"G ",
	"G#",
	"A ",
	"A#",
	"B "
};


main()
{
	int	oct, note, i = 0;
	double	freq;
	SVFCoef coef;
	printf("Name\t\t\tFrequency\t  MIDI\n");
	for(oct = -2; oct < 9; oct++) {
		for(note = 0; note < 12; note++) {
			printf("%s(%d)\t%14lf[Hz]\t%3d:%02XH", notename[note], oct,
				freq =  220.0*pow(2.0, (double)(i - 69)/12.0), i, i);
			coef = getcoef(freq, Fs, 1.0);
			printf("\t%lf\t%02x\t%04lx\n", coef.Fc, ((int)(coef.Fc*128.0+0.5))
							,(int)(coef.Fc*32768.0+0.5));
			i++;
		}
	}
}


