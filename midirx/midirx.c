/*==========================================================================
	midirx.c:
		You can't change this file.
		You may rewrite contents of midirx_proc.c's functions.
		When you are recieved MIDI, You should call MIRIRx().
		
					Shoichi Ikeda	Oct. 10th 2004
==========================================================================*/

/**** Includes ************************************************************/
#include "midi_def.h"

#include "midirx.h"
/**** Definitions *********************************************************/
#define	NULL_STATUS		0x00
#define	DUMMY_BYTE		0

#define	STATUS_BYTE	0
#define	FIRST_BYTE	1
#define	SECOND_BYTE	2

#ifndef	NULL
#define	NULL ((void *)0)
#endif	/* NULL */

#ifndef	__cplusplus

#ifndef	bool
#define	bool	char
#endif	/* bool */

#ifndef	false
#define	false	0
#endif	/* false */

#ifndef	true
#define	true	!false
#endif	/* true */

#endif	/* __cplusplus */

/**** Typedefs*************************************************************/
typedef void (*MIDIRX_CH_MSG_PROC)(unsigned char channel, unsigned char byte1, unsigned char byte2, char stream);
typedef void (*MIDIRX_SYSTEM_COMMON_PROC)(unsigned char byte1, unsigned char byte2, char stream);
typedef void (*MIDIRX_SYSTEM_REALTIME_PROC)(char stream);

/**** External Variables *************************************************/
#ifdef	__cplusplus
extern C {
#endif	/* __cplusplus */

extern const MIDIRX_CH_MSG_PROC midiRxChannelMeessageProc[((PITCHBEND_STATUS - NOTEOFF_STATUS)>>4) + 1];
extern const MIDIRX_SYSTEM_COMMON_PROC midiRxSystemCommonProc[TUNEREQ_STATUS - MTC_STATUS + 1];
extern const MIDIRX_SYSTEM_REALTIME_PROC midiRxSystemRealTimeProc[RESET_STATUS - CLOCK_STATUS + 1];

/**** External Function Prototypes ****************************************/

extern bool MidiRxGetData(unsigned char *data, char stream);
extern void MidiRxStartOfExclusive(char stream);
extern void MidiRxDataOfExclusive(unsigned char data, char stream);
extern void MidiRxEndOfExclusive(char stream);

#ifdef	__cplusplus
}
#endif	/* __cplusplus */

/**** Static Variables ****************************************************/
static unsigned char status[NUMOF_MIDIRX_STREAM];
static unsigned char datum[NUMOF_MIDIRX_STREAM][2];
static char thisByte[NUMOF_MIDIRX_STREAM];
static char endOfByte[NUMOF_MIDIRX_STREAM];
static bool inExclusive[NUMOF_MIDIRX_STREAM];

/**** Static Function's Prototypes!****************************************/

static bool IsChannelMessage(unsigned char status);
static bool IsSystemExclusiveMessage(unsigned char status);
static bool IsSystemCommonMessage(unsigned char status);
static bool IsSystemRealTimeMessage(unsigned char status);
static char DataByteLength(unsigned char status);
static void HandleStatus(unsigned char status, char stream);
static void HandleData(unsigned char data, char stream);
static void HandleChannelMessage(unsigned char status, unsigned char byte1, unsigned char byte2, char stream);
static void HandleSystemCommon(unsigned char status, unsigned char byte1, unsigned char byte2, char stream);
static void HandleSystemRealTime(unsigned char status, char stream);
static void SetStatus(unsigned char data, char stream);
static void ClearStatus(char stream);

/**** Global Functions ****************************************************/
/*--------------------------------------------------------------------------
	Initialize MIDI RX Routin's variables
	param: 	0 <= stream < NUMOF_MIDIRX_STREAM
	return:	none
--------------------------------------------------------------------------*/
void MidiRxInit(char stream)
{
	ClearStatus(stream);
	thisByte[stream] = STATUS_BYTE;
	endOfByte[stream] = STATUS_BYTE;
	inExclusive[stream] = false;
}

/*--------------------------------------------------------------------------
	MIDI RX Routine
		This function call midirx_proc.c's functions.
	param: 	0 <= stream < NUMOF_MIDIRX_STREAM
	return:	none
--------------------------------------------------------------------------*/
void MidiRx(char stream)
{
	unsigned char data;

	while(MidiRxGetData(&data, stream)) {			
		if(STATUS_MASK & data) {
			HandleStatus(data, stream);
		} else {
			HandleData(data, stream);
		}
	}
}

/**** Static Functions ***************************************************/
/*--------------------------------------------------------------------------
	Handle Status Byte
	param: 	status is status byte	
		0 <= stream < NUMOF_MIDIRX_STREAM
	return:	none
--------------------------------------------------------------------------*/
static void HandleStatus(unsigned char status, char stream)
{
	if(IsSystemRealTimeMessage(status)) {
		HandleSystemRealTime(status, stream);
		return;
	}

	if(inExclusive[stream]) {
		MidiRxEndOfExclusive(stream);
		inExclusive[stream] = false;
	}
	
	SetStatus(status, stream);

	if(IsSystemExclusiveMessage(status)) {
		MidiRxStartOfExclusive(stream);
		inExclusive[stream] = true;
	} else {
		endOfByte[stream] = DataByteLength(status);
		thisByte[stream] = STATUS_BYTE;
		if(endOfByte[stream] <= thisByte[stream]) {
			if(IsSystemCommonMessage(status)) {
				HandleSystemCommon(status, DUMMY_BYTE, DUMMY_BYTE, stream);
			}
		}
	}
}

/*--------------------------------------------------------------------------
	Handle Data Byte
	param: 	data is data byte	
		0 <= stream < NUMOF_MIDIRX_STREAM
	return:	none
--------------------------------------------------------------------------*/
static void HandleData(unsigned char data, char stream)
{
	if(inExclusive[stream]) {
		MidiRxDataOfExclusive(data, stream);
	} else {
		thisByte[stream]++;
		switch(thisByte[stream]) {
		case FIRST_BYTE:
			datum[stream][0] = data;
			break;
		case SECOND_BYTE:
			datum[stream][1] = data;
			break;
		default:
			break;
		}
		if(endOfByte[stream] <= thisByte[stream]) {
			if(IsChannelMessage(status[stream])) {
				HandleChannelMessage(status[stream], datum[stream][0], datum[stream][1], stream);
			} else {
				if(IsSystemCommonMessage(status[stream])) {
					HandleSystemCommon(status[stream], datum[stream][0], datum[stream][1], stream);
				}
			}
			thisByte[stream] = STATUS_BYTE;
		}
	}
}

/*--------------------------------------------------------------------------
	Handle Channnel Messages (0x8n - 0xEn)
	param: 	status
		byte1, byte2 = data byte	
		0 <= stream < NUMOF_MIDIRX_STREAM
	return:	none
--------------------------------------------------------------------------*/
static void HandleChannelMessage(unsigned char status, unsigned char byte1, unsigned char byte2, char stream)
{
	int n = ((CHANNEL_MSG_MASK & status) - CHANNEL_MSG)>>4;

	(*(midiRxChannelMeessageProc[n]))(CHANNEL_MASK & status, byte1, byte2, stream);
}

/*--------------------------------------------------------------------------
	Handle System Common Messages (0xF1 - 0xF6),
		 except End of Exclusive (0xF7) 
	param: 	status
		byte1, byte2 = data byte	
		0 <= stream < NUMOF_MIDIRX_STREAM
	return:	none
--------------------------------------------------------------------------*/
static void HandleSystemCommon(unsigned char status, unsigned char byte1, unsigned char byte2, char stream)
{
	int n = status - SYSTEM_COMMON_MSG;
	(*(midiRxSystemCommonProc[n]))(byte1, byte2, stream);
	ClearStatus(stream);
}

/*--------------------------------------------------------------------------
	Handle System Real Time  Messages (0xF8 - 0xFF)
	param: 	status
		byte1, byte2 = data byte	
		0 <= stream < NUMOF_MIDIRX_STREAM
	return:	none
--------------------------------------------------------------------------*/
static void HandleSystemRealTime(unsigned char status, char stream)
{
	int n = status - SYSTEM_REALTIME_MSG;
	
	(*(midiRxSystemRealTimeProc[n]))(stream);
}

/*--------------------------------------------------------------------------
	Checking Status
	param: 	status
	return:	true or false
--------------------------------------------------------------------------*/
static bool IsChannelMessage(unsigned char status)
{
	return (CHANNEL_MSG <= status) && (status < SYSTEM_MSG);
}

static bool IsSystemExclusiveMessage(unsigned char status)
{
	return EXCLUSIVE_STATUS == status;
}

static bool IsSystemCommonMessage(unsigned char status)
{
	return	(SYSTEM_COMMON_MSG <= status) && (status <= TUNEREQ_STATUS);
}

static bool IsSystemRealTimeMessage(unsigned char status)
{
	return	(SYSTEM_REALTIME_MSG <= status) /* && (status <= RESET_STATUS) */;
}


/*--------------------------------------------------------------------------
	Determin Data Byte Length of each messages.
	param: 	status
	return:	data byte length STATUS_BYTE(=0), 
				FIRST_BYTE(=1),
				SECOND_BYTE(=2)
--------------------------------------------------------------------------*/
static char DataByteLength(unsigned char status)
{
	if(IsChannelMessage(status)) {
		switch(CHANNEL_MSG_MASK & status) {
		case NOTEOFF_STATUS:		/* 0x8n */
		case NOTEON_STATUS:		/* 0x9n */
		case POLYPRESS_STATUS:		/* 0xAn */
		case CTRLCHANGE_STATUS:		/* 0xBn */
			return SECOND_BYTE;
			break;
		case PROGCHANGE_STATUS:		/* 0xCn */
		case CHPRESS_STATUS:		/* 0xDn */
			return FIRST_BYTE;
			break;
		case PITCHBEND_STATUS:		/* 0xEn */
			return SECOND_BYTE;
			break;
		default:
			break;
		}
	} else {
		switch(status) {
		case MTC_STATUS:		/* 0xF1 */
			return FIRST_BYTE;
			break;
		case SONGPOSITION_STATUS:	/* 0xF2 */
			return SECOND_BYTE;
			break;
		case SONGSELECT_STATUS:		/* 0xF3 */
			return FIRST_BYTE;
			break;
		case TUNEREQ_STATUS:		/* 0xF6 */
		case CLOCK_STATUS:		/* 0xF8 */
		case START_STATUS:		/* 0xFA */
		case CONTINUE_STATUS:		/* 0xFB */
		case STOP_STATUS:		/* 0xFC */
		case ACTIVESENS_STATUS:		/* 0xFE */
		case RESET_STATUS:		/* 0xFF */
			return STATUS_BYTE;
			break;
		case EXCLUSIVE_STATUS:		/* 0xF0 */
		case UNDEF1_STATUS:		/* 0xF4 */
		case UNDEF2_STATUS:		/* 0xF5 */
		case ENDOFEX_STATUS:		/* 0xF7 */
		case UNDEF3_STATUS:		/* 0xF9 */
		case UNDEF4_STATUS:		/* 0xFD */
		default:
			return STATUS_BYTE;
			break;
		}
	}
}

/*--------------------------------------------------------------------------
	Set and Clear staus[] variables.
	param: 	data is new status	
		0 <= stream < NUMOF_MIDIRX_STREAM
	return:	 none
--------------------------------------------------------------------------*/
static void SetStatus(unsigned char data, char stream)
{
	status[stream] = data;
}

static void ClearStatus(char stream)
{
	status[stream] = NULL_STATUS;
}

/*==========================================================================
	End
==========================================================================*/
