/*==============================================================================
	mkslot.c:	Make Slot define from CSP Symbol File
		$Header$
==============================================================================*/
#include <stdio.h>

#define	SYM_NUM	1024			/* Max Symbol number */
#define	NAME_LEN	(16+1)		/* Symbol Name Length */  


typedef struct _Slot {			/* Symbol Slot Data */
	int	slot;
	struct _Slot	*next;
} Slot;

typedef struct {			/* Symbol data */
	char	*name;
	Slot	*slot;
} Symbol;

Symbol	coef[SYM_NUM], iram[SYM_NUM], eram[SYM_NUM]; 

char	*prog;
char	header[NAME_LEN];

usage()
{
	fprintf(stderr, "\t%s Header_String < CSP_Symbol_file\n", prog);
	exit(-1);
}

main(argc, argv)
int	argc;
char	*argv[];
{
	fprintf(stderr, "%s : Get Slot data from CSP Symbol file.\n",   
							prog = argv[0]);
	if(argc != 2)
		usage();
	if(NAME_LEN <= strlen(argv[1])) {
		fprintf(stderr, "%s: Header String too long!\n", prog); 
		usage();
	}
	strtoupper(header, argv[1]);	
	table_init();
	get_data();
	put_data();	
	return 0;
}

table_init()
{
	int	i;
	for(i = 0; i < SYM_NUM; i++) {
		coef[i].name = NULL;	coef[i].slot = NULL;
		iram[i].name = NULL;	iram[i].slot = NULL;
		eram[i].name = NULL;	eram[i].slot = NULL;
	}
}
	

char *skip_space(p)
char	*p;
{
	while(' ' == *p++) 	{;}
	return p;
} 

get_data()
{
	int	slot, i;
	char	buf[180];
	char	namebuf[16+1];
	char	*p;
	
	while(NULL != (p = gets(buf))) {					
		if('/' == *p)				
			continue;
		p = buf;
		*(p + 4) = '\0';
		slot = atoi(p);
		p += (4+1);
		if(' ' != *p) {
			for(i = 1; i < NAME_LEN+1; i++) {
				if(' ' == *(p+i)) {
					*(p+i) = '\0';
					break;
				}
			}
			strcpy(namebuf, p);	
			Install(namebuf, slot, coef);
		}	
		while(':' != *p++)	{;}
		if(' ' != *p) {
			for(i = 1; i < NAME_LEN; i++) {
				if(' ' == *(p+i)) {
					*(p+i) = '\0';
					break;
				}
			}
			strcpy(namebuf, p);
			Install(namebuf, slot, iram);
		}
		while(':' != *p++)	{;}
		if(' ' != *p) {
			for(i = 1; i < NAME_LEN; i++) {
				if(' ' == *(p+i)) {
					*(p+i) = '\0';
					break;
				}
			}
			strcpy(namebuf, p);
			Install(namebuf, slot, eram);
		}
	}
}

Install(name, slot, table)
char	*name;
int	slot;
Symbol	*table;
{
	Slot	*sp, *p;
	
	while(NULL != table->name) {
		if(0 == strcmp(name, table->name)) {
			break;
		}
		table++;
	}
	if(NULL == table->name) {
		if(NULL == (table->name = (char *)malloc(sizeof(char)*NAME_LEN))) {
			fprintf(stderr, "%s: Memory no enough\n", prog);
			exit(-2);
		}
		strcpy(table->name, name);
		if(NULL == (table->slot = (Slot *)malloc(sizeof(Slot)))) {
			fprintf(stderr, "%s: Memory no enough\n", prog);
			exit(-2);
		}
		table->slot->slot = slot;
		table->slot->next = NULL;	
	} else {
		if(NULL == (sp = (Slot *)malloc(sizeof(Slot)))) {
			fprintf(stderr, "%s: Memory no enough\n", prog);
			exit(-2);
		}
		p = table->slot;
		while(NULL != p->next) {
			p = p->next;	
		}
		p->next = sp;
		sp->slot = slot;
		sp->next = NULL;	
	}
}
	
		
	
put_data()
{
	Symbol	*p;
	Slot	*sp;

	printf("/*---- COEF -------------------------- slot --\
--------------------------------*/\n");	
	p = coef;
	print_sym(p);
	putchar('\n');

	printf("/*---- IRAM -------------------------- slot --\
--------------------------------*/\n");	
	p = iram;
	print_sym(p);
	putchar('\n');

	printf("/*---- ERAM -------------------------- slot --\
--------------------------------*/\n");	
	p = eram;
	print_sym(p);
}
	
print_sym(p)
Symbol	*p;
{
	Slot	*sp;
	while(NULL != p->name) {
		int	count = 1;	
		sp = p->slot;
		print_def(header, p->name, sp->slot, count);
		while(NULL != sp->next) {
			count++;
			sp = sp->next;
			print_def(header, p->name, sp->slot, count);
		}
		p++;	
	}
}

print_def(head, name, slot, count)
char	*head, *name; 
int	slot, count;
{
	int	dis;
	char	num[5];

	printf("#define	%s_%s", head, name);
	dis = 30 - strlen(header) - strlen(name);
	if(count > 1) { 
		sprintf(num, "_%d", count);
		dis -=  strlen(num);
		printf("%s", num);
	}
	for(; dis > 0; dis--)
		putchar(' ');					
	printf("%4d\n", slot);
}

strtoupper(dst, src)
char	*dst, *src;
{
	while('\0' != *src) {
		*dst++ = toupper(*src++);
	}
	dst++;
	*dst = '\0';
}
