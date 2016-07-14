#include <stdio.h>
#include <stdlib.h>

char	*prog;
char	buf[128];
int		slot;
long	pram[1024];


main(argc, argv)
char	*argv[];
{
	char	tmp[40];
	char	*p;

	prog = argv[0];
	if(argc != 2)
		fprintf(stderr, "%s Error: need more argument\n", prog);
	while(NULL != gets(buf)) {
		if('/' == *buf)	continue;
		if(':' != *(buf+4)) {
			fprintf(stderr, "%s Error: Unexpected ':'\n", prog);	
			exit(-1);
		}
		*(buf+4) = 0;
		sscanf(buf, "%d", &slot);
		if((slot < 0) || (1024 <= slot)) {
			fprintf(stderr, "Error: slot number err slot is %d\n", slot);
			exit(-2);
		}
		*(buf+29) = 0;
		sscanf((buf+5), "%s", tmp);
		pram[slot] = strtol(tmp, &p, 2);
	}

	printf("long pram_%s[1024] = {\n", argv[1]);
	for(slot = 0; slot < 1024; slot++) {
		if(0 == (slot%4))
			putchar('\t');
		printf("0x%06lxL, ", pram[slot]);
		if(3 == (slot%4))
			printf("\n");
	}
	printf("};\n\n");
}
