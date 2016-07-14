#include <iostream.h>
#include <math.h>

#include "s2z.h"
#include "printCoef.h"


int main(void)
{
	double	lp, bp, hp;
	double	freq, q;

	double	s[2][3], z[2][3];

	cerr << "LP:	";	cin >> lp;
	cerr << "BP:	";	cin >> bp;
	cerr << "HP:	";	cin >> hp;

	cerr << "Freq:	";	cin >> freq;
	cerr << "Q:	";	cin >> q;

	s[1][0] = 1.0;
	s[1][1] = 1.0/2.0/M_PI/freq/q;
	s[1][2] = 1.0/2.0/2.0/M_PI/M_PI/freq/freq;

	s[0][0] = s[1][0] * lp;
	s[0][1] = s[1][1] * bp;
	s[0][2] = s[1][2] * hp;

	s2z(s[0], s[1], z[0], z[1], 2, 1.0/44100.0);


	for(int j = 0; j < 3; j++) {
		printCoef(z[0][j]);
	}

	for(int j = 1; j < 3; j++) {
		printCoef(-z[1][j]);
	}
}
