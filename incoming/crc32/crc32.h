/*==========================================================================
	crc32.h: 
	$Author$
	$Revision$
	$Date$
==========================================================================*/
#ifndef _CRC32_H
#define _CRC32_H

/*****  Includes **********************************************************/

/*****  Definitions  ******************************************************/

/*****  Enums *************************************************************/

/*****  Typedefs  *********************************************************/

/*****  External Variables  ***********************************************/

/*****  External Function's Prototypes  ***********************************/
#ifdef __cplusplus
extern "C" {
#endif

/* crc32.c */
extern unsigned long crc(unsigned char *buf, int len);
extern void CRC32Init(unsigned long crc);
extern unsigned long CRC32Update(unsigned char data);
extern unsigned long CRC32Result(void);

#ifdef __cplusplus
}
#endif


#endif /* _CRC32_H */
/*==========================================================================
	End
==========================================================================*/
