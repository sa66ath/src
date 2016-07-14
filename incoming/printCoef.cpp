
#include <iostream.h>
#include <stdlib.h>

#include "printCoef.h"

void printCoef(double d)
{
	int	shift = 0;
	long	hexv;

	if(d < 0.0) {
		hexv = 16384 * d - 0.5;
	} else {
		hexv = 16384 * d + 0.5;
	}

	if((hexv < -16384) || (16384 <= hexv)) {
		hexv >>= 1;
		shift = 1;
	}
	
	if((hexv < -16384) || (16384 <= hexv)) {
		hexv >>= 1;
		shift = 2;
	}
	
	if((hexv < -16384) || (16384 <= hexv)) {
		hexv >>= 2;
		shift = 4;
	}

	hexv <<= 1;

	hexv &= 0xffff;

	cout << "0x" << hex << hexv << "	// shift " << shift << endl;
}

#ifdef	MODULE_DEBUG
int main(int argc, char* argv[])
{
	double	d;	

	d = atof(argv[1]); 
	printCoef(d);
}
#endif	/* MODULE_DEBUG */
