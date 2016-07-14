#include <stdio.h>
#include <math.h>

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


double	freq;

main()
{
	int	oct, note, i = 0;
	printf("Name\tFrequency[Hz]\tRate[msec]\t  MIDI\n");
	for(oct = -2; oct < 9; oct++) {
		for(note = 0; note < 12; note++) {
			printf("%s(%d)\t%14lf\t%10lf\t%3d:%02XH\n", notename[note], oct,
				 freq = 220.0*pow(2.0, (double)(i - 69)/12.0), 1000.0/freq, i, i);
				i++;
		}
	}
}
