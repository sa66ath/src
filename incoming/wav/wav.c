/*==========================================================================
	wav.c: 'WAV' File
	$Header$
==========================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <math.h>

#include "wav.h"


/*
#define	ALONE_DEBUG
*/

#define	ID_LEN		4

#define	RiffID		"RIFF"
#define	RiffType	"WAVE"
#define	FormatID	"fmt "
#define	DataID		"data"

#define	NO_COMPRESSION	1


/*
	Static Function's Prototype
*/
static void changeEndian(void *data, size_t size);
static size_t readHeader(WaveChunk *chunk, FILE *fp);
static size_t writeHeader(WaveChunk *chunk, FILE *fp);
static size_t readFormatChunk(FormatChunk *chunk, FILE *fp);
static size_t writeFormatChunk(FormatChunk *chunk, FILE *fp, UWORD channels, UDWORD samplesPerSec, UWORD bitsPerSample);
static size_t readDataHeader(DataChunk *chunk, FILE *fp);
static size_t writeDataHeader(DataChunk *chunk, FILE *fp);

/*--------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
	prog  :	ikeda
	func  :	WAV File Open as Read
	date  :	2002年12月18日 (水) 14時25分31秒 JST
	entry :	filename = File Name
	return: WAVFILE*. If error occured, the function return null pointer
	remks :	---
-----------------------------------------------------------------------------*/
WAVFILE* wavReadFOpen(const char* filename)
{
	WAVFILE* wf;

	if(NULL == (wf = malloc(sizeof(WAVFILE)))) {
		return NULL;
	}

	if(NULL == (wf->fp = fopen(filename, "rb"))) {
		wavFClose(wf);
		return NULL;	
	}

	strcpy(wf->mode, "rb");

	readHeader(&wf->waveChunk, wf->fp);

	if(strncmp(RiffID, wf->waveChunk.groupID, 4)) {
		wavFClose(wf);
		return NULL;
	}
		
	if(strncmp(RiffType, wf->waveChunk.riffType, 4)) {
		wavFClose(wf);
		return NULL;
	}

	readFormatChunk(&wf->waveChunk.format, wf->fp);

	if(strncmp(FormatID, wf->waveChunk.format.chunkID, 4)) {
		wavFClose(wf);
		return NULL;
	}

	if(1 != wf->waveChunk.format.wFormatTag) {
		wavFClose(wf);
		return NULL;
	}

	readDataHeader(&wf->waveChunk.data, wf->fp);
	if(strncmp(DataID, wf->waveChunk.data.chunkID, 4)) {
		wavFClose(wf);
		return NULL;
	}

	return wf;
}

/*-----------------------------------------------------------------------------
	prog  :	ikeda
	func  :	WAV File Open as Write
	date  :	2002年12月18日 (水) 14時25分31秒 JST
	entry :	filename = File Name
		channels = 1(Mono) or 2(Stereo)
		samplePerSec = Sampling Frequncy (Hz)
		bitPerSample = data bit 8/16/32
	return: WAVFILE*. If error occured, the function return null pointer
	remks :	---
-----------------------------------------------------------------------------*/
WAVFILE* wavWriteFOpen(const char *filename, UWORD channels, UDWORD samplesPerSec, UWORD bitsPerSample)
{
	WAVFILE* wf;

	if(NULL == (wf = malloc(sizeof(WAVFILE)))) {
		return NULL;
	}

	if(NULL == (wf->fp = fopen(filename, "wb"))) {
		wavFClose(wf);
		return NULL;	
	}

	strcpy(wf->mode, "wb");

	writeHeader(&wf->waveChunk, wf->fp);
	writeFormatChunk(&wf->waveChunk.format, wf->fp, channels, samplesPerSec, bitsPerSample);
	writeDataHeader(&wf->waveChunk.data, wf->fp);

	return wf;
}



/*-----------------------------------------------------------------------------
	prog  :	ikeda
	func  :	The wavFRead() function reads into an array pointed to  by  ptr
		up  to  nitems  items  of data from WAVFILE stream, where 
		an item of It stops reading bytes if an end-of-file 
		or error condition is encountered while  reading stream,
		or  if  nitems items have been read.  It increments
		the data pointer in stream to point to  the  byte  following
		the  last byte read if there is one.
		It does not change the contents of stream. 
		It returns the number of items read.
	date  :	2002年12月18日 (水) 14時26分29秒 JST
	entry : ptr = data array pointer to be stored.
		size = byte size of each data. 1(8bit), 2(16bit), 4(32bit)
		nitems = number of elements to read.
	return: number of items read.
	remks :	---
-----------------------------------------------------------------------------*/
size_t wavFRead(void *ptr, size_t size, size_t nitems, WAVFILE *stream)
{
	int n;
	size_t ret = 0;
	WORD	word;
	DWORD	dword;
	char* cp = ptr;
	
	for(n = 0; n < nitems; n++) {
		switch(size) {
		case 1:
			ret += fread(cp++, size, 1, stream->fp);
			break;
		case 2:
			ret += fread(&word, size, 1, stream->fp);
			changeEndian(&word, sizeof(WORD));
			*((WORD*)ptr) = word;
			((WORD*)ptr)++;
			break;
		case 4:
			ret += fread(&dword, size, 1, stream->fp);
			changeEndian(&dword, sizeof(DWORD));
			*((DWORD*)ptr) = dword;
			((DWORD*)ptr)++;
			break;
		default:
			return 0;
		}
		stream->waveChunk.data.remain -= size;
	}
	return ret;
}


/*-----------------------------------------------------------------------------
	prog  :	ikeda

	func  :	The wavFWrite() function writes to the named output 
		WAVFILE stream at most nitems items of data 
		from the array pointed to by ptr,
		where an item of data is a sequence of bytes (not necessarily
		terminated by a null byte) of length size. 
		It stops writing when it has written nitems items of data 
		or if an error  condition is encountered on stream.
		It does not change the contents of the array pointed to by ptr.
		It increments the data pointer in stream by the number of bytes
		written and returns the number of items written.

	date  :	2002年12月18日 (水) 14時29分30秒 JST

	entry : ptr = data array pointer
		size = byte size of each data. 1(8bit), 2(16bit), 4(32bit)
		nitems = number of elements to read.
	return: number of items write.
	remks :	---
-----------------------------------------------------------------------------*/
size_t wavFWrite(const void *ptr, size_t size, size_t nitems, WAVFILE *stream)
{
	int n;
	size_t ret = 0;
	WORD	word;
	DWORD	dword;
	char* cp;
	
	for(n = 0; n < nitems; n++) {
		switch(size) {
		case 1:
			ret += fwrite(cp++, size, 1, stream->fp);
			break;
		case 2:
			word = *((WORD*)ptr);
			changeEndian(&word, sizeof(WORD));
			ret += fwrite(&word, size, 1, stream->fp);
			((WORD*)ptr)++;
			break;
		case 4:
			dword = *((DWORD*)ptr);
			changeEndian(&dword, sizeof(DWORD));
			ret += fread(&dword, size, nitems, stream->fp);
			((DWORD*)ptr)++;
			break;
		default:
			return 0;
		}
		stream->waveChunk.data.chunkSize += size;
	}
	return ret;
}

/*-----------------------------------------------------------------------------
	prog  :	ikeda
	func  :	
		The wavFClose() function causes the WAVFILE stream pointed
		to by stream to be flushed and the associated file 
		to be closed. 
		Any unwritten buffered data for the stream is written to the
		file;  any unread buffered data is discarded.  The stream is
		disassociated from the file.  If the associated  buffer  was
		automatically  allocated,  it  is deallocated.  It marks for
		update the st_ctime and st_mtime fields  of  the  underlying
		file,  if  the stream was writable, and if buffered data had
		not been written to the file  yet.
		The wavFClose()  function will perform a close(2) 
		on the file descriptor that is associated with the stream 
		pointed to by stream.

		After the call to wavFClose(), any use of stream 
		causes  undefined behavior.

	date  :	2002年12月18日 (水) 14時25分49秒 JST

	entry : stream = WAVFILE stream pointer

	return: Upon successful completion, fclose() returns 0.
		Otherwise, it returns EOF and sets errno to indicate the error.

	remks :	---
-----------------------------------------------------------------------------*/
int wavFClose(WAVFILE* stream)
{
	int ret;

	if('w' == stream->mode[0]) {
		DWORD dword;	
		fflush(stream->fp);
		fseek(stream->fp, stream->waveChunk.data.chunkSize_offset, SEEK_SET);	
		dword = stream->waveChunk.data.chunkSize;
		changeEndian(&dword, sizeof(DWORD));
		fwrite(&dword, sizeof(DWORD), 1, stream->fp);
	}

	ret = fclose(stream->fp);
	free(stream);	

	return ret;
}


/*--------------------------------------------------------------------------*/
/*
	Static Functions
*/
static void changeEndian(void* data, size_t size)
{
	char buf;
	int  i;

	for(i = 0; i < (size>>1); i++) {
		buf = ((char*)data)[i];	
		((char*)data)[i] = ((char*)data)[size - i - 1];
		((char*)data)[size - i - 1] = buf;
	}
}

static size_t readHeader(WaveChunk* chunk, FILE* fp)
{
	size_t count = 0;

	count += fread(chunk->groupID, sizeof(char[4]), 1, fp);
	count += fread(chunk->dummy, sizeof(char[4]), 1, fp);
	count += fread(chunk->riffType, sizeof(char[4]), 1, fp);

	return count;
}

static size_t writeHeader(WaveChunk* chunk, FILE* fp)
{
	size_t count = 0;

	strncpy(chunk->groupID, RiffID, ID_LEN);	
	strncpy(chunk->riffType, RiffType, ID_LEN);	
	count += fwrite(chunk->groupID, sizeof(char[4]), 1, fp);
	count += fwrite("    ", sizeof(char[4]), 1, fp);
	count += fwrite(chunk->riffType, sizeof(char[4]), 1, fp);

	return count;
}
	

static size_t readFormatChunk(FormatChunk* chunk, FILE* fp)
{
	size_t count = 0;

	count += fread(chunk->chunkID, sizeof(char[4]), 1, fp); 

	count += fread((DWORD*)&chunk->chunkSize, sizeof(DWORD), 1, fp); 
	changeEndian(&chunk->chunkSize, sizeof(DWORD));

	count += fread((WORD*)&chunk->wFormatTag, sizeof(WORD), 1, fp); 
	changeEndian(&chunk->wFormatTag, sizeof(WORD));

	count += fread((UWORD*)&chunk->wChannels, sizeof(UWORD), 1, fp); 
	changeEndian(&chunk->wChannels, sizeof(UWORD));

	count += fread((UDWORD*)&chunk->dwSamplesPerSec, sizeof(UDWORD), 1, fp); 
	changeEndian(&chunk->dwSamplesPerSec, sizeof(UDWORD));

	count += fread((UDWORD*)&chunk->dwAvgBytesPerSec, sizeof(UDWORD), 1, fp); 
	changeEndian(&chunk->dwAvgBytesPerSec, sizeof(UDWORD));

	count += fread((UWORD*)&chunk->wBlockAlign, sizeof(UWORD), 1, fp); 
	changeEndian(&chunk->wBlockAlign, sizeof(UWORD));

	count += fread((UWORD*)&chunk->wBitsPerSample, sizeof(UWORD), 1, fp); 
	changeEndian(&chunk->wBitsPerSample, sizeof(UWORD));

	for(; count < chunk->chunkSize - 8; ) {
		char dummy;
		count += fread(&dummy, 1, 1, fp); 
	}

	return count;
}

static size_t writeFormatChunk(FormatChunk* chunk, FILE* fp, UWORD channels, UDWORD samplesPerSec, UWORD bitsPerSample)
{
	WORD	word;	
	UWORD	uword;
	DWORD	dword;
	UDWORD	udword;
	size_t count = 0;

	strncpy(chunk->chunkID, FormatID, ID_LEN);
	count += fwrite(chunk->chunkID, sizeof(char[4]), 1, fp); 

	dword = chunk->chunkSize = 0x10;
	changeEndian(&dword, sizeof(DWORD));
	count += fwrite(&dword, sizeof(DWORD), 1, fp); 

	word = chunk->wFormatTag = NO_COMPRESSION;
	changeEndian(&word, sizeof(WORD));
	count += fwrite(&word, sizeof(WORD), 1, fp); 

	uword = chunk->wChannels = channels;	
	changeEndian(&uword, sizeof(UWORD));
	count += fwrite(&uword, sizeof(UWORD), 1, fp); 

	udword = chunk->dwSamplesPerSec = samplesPerSec;	
	changeEndian(&udword, sizeof(UDWORD));
	count += fwrite(&udword, sizeof(UDWORD), 1, fp); 

	uword = chunk->wBlockAlign = ceil(channels * bitsPerSample / 8.0);
	udword = chunk->dwAvgBytesPerSec = ceil(samplesPerSec * chunk->wBlockAlign);
	changeEndian(&udword, sizeof(UDWORD));
	count += fwrite(&udword, sizeof(UDWORD), 1, fp); 
	
	changeEndian(&uword, sizeof(UWORD));
	count += fwrite(&uword, sizeof(UWORD), 1, fp); 

	uword = chunk->wBitsPerSample = bitsPerSample;
	changeEndian(&uword, sizeof(UWORD));
	count += fwrite(&uword, sizeof(UWORD), 1, fp); 

	return count;
}

static size_t readDataHeader(DataChunk* chunk, FILE* fp)
{
	size_t	count = 0;

	count += fread(chunk->chunkID, sizeof(char[4]), 1, fp); 
	
	count += fread(&chunk->chunkSize, sizeof(DWORD), 1, fp); 
	changeEndian(&chunk->chunkSize, sizeof(DWORD));

	chunk->remain = chunk->chunkSize;

	return count;
}


static size_t writeDataHeader(DataChunk* chunk, FILE* fp)
{
	size_t	count = 0;
	
	strncpy(chunk->chunkID, DataID, ID_LEN);
	count += fwrite(chunk->chunkID, sizeof(char[4]), 1, fp); 
	
	chunk->chunkSize_offset = ftell(fp);

	chunk->chunkSize = 0;
	changeEndian(&chunk->chunkSize, sizeof(DWORD));
	count += fwrite(&chunk->chunkSize, sizeof(DWORD), 1, fp); 

	return count;
}

/***************************************************************************/
#ifdef	ALONE_DEBUG

int printID(char* cp, FILE* stream)
{
	int	i;
	for(i = 0; i < sizeof(char[4]); i++)
		putc(cp[i], stream);
}

int main(int argc, char **argv)
{
	int i;
	WAVFILE		*rfp, *wfp;
	FormatChunk	format;
	DataChunk	dataHeader;
	DWORD		dword;
	char		c;

	if(argc < 2)	return 0;

	if(NULL == (rfp = wavReadFOpen(argv[1]))) {
		fprintf(stderr, "Can't open '%s'\n", argv[1]);
		return -1;
	}

	printID(rfp->waveChunk.groupID, stdout); putchar('\n');
	printID(rfp->waveChunk.riffType, stdout); putchar('\n');

	printID(rfp->waveChunk.format.chunkID, stdout); putchar('\n');
	printf("chunkSize = %d\n", rfp->waveChunk.format.chunkSize);
	printf("Format = %d\n", rfp->waveChunk.format.wFormatTag);
	printf("Channels = %d\n", rfp->waveChunk.format.wChannels);
	printf("Samples Per Sec = %d\n", rfp->waveChunk.format.dwSamplesPerSec);
	printf("Avg Bytes Per Sec= %d\n", rfp->waveChunk.format.dwAvgBytesPerSec);
	printf("Block Align = %d\n", rfp->waveChunk.format.wBlockAlign);
	printf("Bit Per Sample = %d\n", rfp->waveChunk.format.wBitsPerSample);

	printf("Data Size = %d\n", rfp->waveChunk.data.chunkSize);


	if(argc < 3)	return 0;

	if(NULL == (wfp = wavWriteFOpen(argv[2], rfp->waveChunk.format.wChannels, rfp->waveChunk.format.dwSamplesPerSec, rfp->waveChunk.format.wBitsPerSample))) {
		fprintf(stderr, "Can't open '%s'\n", argv[1]);
	}

	for( ; wavFRead(&c, rfp->waveChunk.format.wBitsPerSample/8, 1, rfp); ) {
		wavFWrite(&c, wfp->waveChunk.format.wBitsPerSample/8, 1, wfp);
	}

	wavFClose(rfp);
	wavFClose(wfp);

	return 0;
}


#endif	/* ALONE_DEBUG */
/***************************************************************************/
/*==========================================================================
	$Log$
==========================================================================*/
