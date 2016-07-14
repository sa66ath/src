#include <stdio.h>

main()
{
	long	hex, midi;

	while(printf("HEX	"), EOF != scanf("%lx%*c", &hex)) {
		midi = 0x00007fL & (hex>>14);
		midi <<= 8;
		midi |= 0x00007fL & (hex>>7);
		midi <<= 8;
		midi |= 0x00007fL & hex;
		printf("MIDI	%06lx\n", midi);
	}
}
