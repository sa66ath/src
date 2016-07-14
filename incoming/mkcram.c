#include <stdio.h>
#include <stdlib.h>

char	*prog;
char	buf[128];
int	slot;
int	cram[1024];


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
		*(buf+45) = 0;
		sscanf((buf+29), "%s", tmp);
		cram[slot] = (int)strtol(tmp, &p, 2);
	}
	printf("int cram_%s[1024] = {\n", argv[1]);
	for(slot = 0; slot < 1024; slot++) {
		if(0 == (slot%8))
			putchar('\t');
		printf("0x%04x, ", cram[slot]);
		if(7 == (slot%8))
			printf("\n");
	}
	printf("};\n\n");
}
