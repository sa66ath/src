/*============================================================================
	wav.h: 'WAV' File
	$Header$
============================================================================*/
#ifndef	__WAV_H
#define	__WAV_H

#include <stdio.h>

typedef	short		WORD;		/* 2 Bytes */
typedef	unsigned short	UWORD;		/* 2 Bytes */
typedef	long		DWORD;		/* 4 Bytes */
typedef	unsigned long	UDWORD;		/* 4 Bytes */

typedef struct {
	char	chunkID[4];
	DWORD	chunkSize;
	WORD	wFormatTag;
	UWORD	wChannels;
	UDWORD	dwSamplesPerSec;
	UDWORD	dwAvgBytesPerSec;
	UWORD	wBlockAlign;	
	UWORD	wBitsPerSample;	
} FormatChunk;

typedef struct {
	char	chunkID[4];
	DWORD	chunkSize;
	long	remain;			/* in read: remain, in write: write num */
	long	chunkSize_offset;	/* Data Chunk Size seek pointer */
} DataChunk;


typedef struct {
	char		groupID[4];	/* 'RIFF' */
	char		dummy[4];
	char		riffType[4];	/* 'WAVE' */
	FormatChunk	format;
	DataChunk	data;
} WaveChunk;


typedef struct {
	FILE*		fp;
	char		mode[4];
	WaveChunk	waveChunk;
} WAVFILE;

/*--------------------------------------------------------------------------
	Function's Prototypes
--------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------------
	prog  :	ikeda
	func  :	WAV File Open as Read
	date  :	2002年12月18日 (水) 14時25分31秒 JST
	entry :	filename = File Name
	return: WAVFILE*. If error occured, the function return null pointer
	remks :	---
-----------------------------------------------------------------------------*/
extern WAVFILE *wavReadFOpen(const char *filename);

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
extern WAVFILE *wavWriteFOpen(const char *filename, UWORD channels, UDWORD samplesPerSec, UWORD bitsPerSample);


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
extern size_t wavFRead(void *ptr, size_t size, size_t nitems, WAVFILE *stream);

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
extern size_t wavFWrite(const void *ptr, size_t size, size_t nitems, WAVFILE *stream);

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
extern int wavFClose(WAVFILE *stream);

#ifdef __cplusplus
}
#endif

/*--------------------------------------------------------------------------*/
#endif	/* __WAV_H */
/*============================================================================
	$Log$	
============================================================================*/
