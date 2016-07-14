#include <stdio.h>

#include "crc32.h"

int main(int argc, char *argv[]) 
{
	int ret = 0;
	FILE* fp;
	unsigned char data;
	unsigned long len;

	switch(argc) {
	case 2:
		fp = fopen(argv[1], "rb");
		if(!fp) {
			fprintf(stderr, "Can't open file '%s'\n", argv[1]);
			return -1;
		}
		break;
	default:
		return 0;
		break;
	}

	CRC32Init(0xffffffffL);

	for(len = 0; fread(&data, 1, 1, fp); len++) {
		CRC32Update(data);
	}

	printf("CRC32 = 0x%08x\n", CRC32Result());
	printf("len = %ld\n", len);

	return ret;
}




