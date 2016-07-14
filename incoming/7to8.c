#include <stdio.h>

main(int argc, char *argv[])
{
	long	midi;
	long	hex;

	if(argc == 1) {
		while(printf("MIDI	"), EOF != scanf("%lx%*c", &midi)) {
			hex = 0x00007fL & (midi>>24);	
			hex <<= 7;
			hex |= 0x00007fL & (midi>>16);	
			hex <<= 7;
			hex |= 0x00007fL & (midi>>8);
			hex <<= 7;
			hex |= 0x00007fL & midi;
			printf("HEX	");	printf("%08lx\n", hex);
		}
	} else {
		if(('-' == *argv[1]) && ('n' == *(argv[1]+1))) {
			scanf("%lx%*c", &midi);
			hex = 0x00007fL & (midi>>24);	
			hex <<= 7;
			hex |= 0x00007fL & (midi>>16);	
			hex <<= 7;
			hex |= 0x00007fL & (midi>>8);
			hex <<= 7;
			hex |= 0x00007fL & midi;
			printf("0x%08lxL\n", hex);
		}
	}
	return 0;
}
