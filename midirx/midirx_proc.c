/*==========================================================================
	midirx_proc.c:
		These Global functions and variables are used by only midirx.c
		You can rewrite contents of functions.
		
					Shoichi Ikeda	Oct. 10th 2004
==========================================================================*/
/**** Includes*************************************************************/
#include "midi_def.h"

/**** Definitions *********************************************************/
#define	ALONE_DEBUG	/* Module Debug */

#ifdef	ALONE_DEBUG
#include <stdio.h>
#include "midirx.h"
#endif	/* ALONE_DEBUG */

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


/**** Static Function's Prototypes ****************************************/

static void NoteOff(unsigned char channel, unsigned char noteNumber, unsigned char velocity, char stream);
static void NoteOn(unsigned char channel, unsigned char noteNumber, unsigned char velocity, char stream);
static void PolyKeyPressure(unsigned char channel, unsigned char noteNumber, unsigned char puressure, char stream);
static void ControlChange(unsigned char channel, unsigned char controlNumber, unsigned char controlValue, char stream);
static void ProgramChange(unsigned char channel, unsigned char programNumber, unsigned char dummy, char stream);
static void ChannelPressure(unsigned char channel, unsigned char pressureValue, unsigned char dummy, char stream);
static void PitchBendChange(unsigned char channel, unsigned char lsb, unsigned char msb, char stream);
static void MTCQuarterFrame(unsigned char typeValue, unsigned char dummy, char stream);
static void SongPositionPointer(unsigned char lsb, unsigned char msb, char stream);
static void SongSelect(unsigned char songNumber, unsigned char dummy, char stream);
static void TuneRequest(unsigned char dummy0, unsigned char dummy1, char stream);
static void EndOfExclusive(unsigned char dummy0, unsigned char dummy1, char stream);
static void UndefF4(unsigned char dummy0, unsigned char dummy1, char stream);
static void UndefF5(unsigned char dummy0, unsigned char dummy1, char stream);
static void TimingClock(char stream);
static void Start(char stream);
static void Continue(char stream);
static void Stop(char stream);
static void ActiveSensing(char stream);
static void SystemReset(char stream);
static void UndefF9(char stream);
static void UndefFD(char stream);


/**** Global Variables ****************************************************/
const MIDIRX_CH_MSG_PROC midiRxChannelMeessageProc[((PITCHBEND_STATUS - NOTEOFF_STATUS)>>4) + 1] = {
	NoteOff,		/* 0x8n */
	NoteOn,			/* 0x9n */
	PolyKeyPressure,	/* 0xAn */
	ControlChange,		/* 0xBn */
	ProgramChange,		/* 0xCn */
	ChannelPressure,	/* 0xDn */
	PitchBendChange,	/* 0xEn */
};

const MIDIRX_SYSTEM_COMMON_PROC midiRxSystemCommonProc[TUNEREQ_STATUS - MTC_STATUS + 1] = {
	MTCQuarterFrame,	/* 0xF1 */
	SongPositionPointer,	/* 0xF2 */
	SongSelect,		/* 0xF3 */
	UndefF4,		/* 0xF4 */
	UndefF5,		/* 0xF5 */
	TuneRequest,		/* 0xF6 */
};

const MIDIRX_SYSTEM_REALTIME_PROC midiRxSystemRealTimeProc[RESET_STATUS - CLOCK_STATUS + 1] = {
	TimingClock,	/* 0xF8 */
	UndefF9,	/* 0xF9 */
	Start,		/* 0xFA */
	Continue,	/* 0xFB */
	Stop,		/* 0xFC */
	UndefFD,	/* 0xFD */
	ActiveSensing,	/* 0xFE */
	SystemReset,	/* 0xFF */
};

/**** Global Functions ****************************************************/
/*--------------------------------------------------------------------------
	Get Received MIDI byte
		This function is call by only midirx.c
		Please modify correctly for your system.
	param:	data is pointer of stroing buffer
		0 <= stream < NUMOF_MIDIRX_STREAM 
	return:	true=storing data, false=no data for stroing	
--------------------------------------------------------------------------*/
bool MidiRxGetData(unsigned char* data, char stream)
{
#ifndef	ALONE_DEBUG

#else /* ALONE_DEBUG */
	int input;

	switch(scanf("%2x", &input)) {
	case 0:
	case EOF:
		return false;
		break;
	case 1:
		*data = 0xff & input;
		return true;
	}
#endif /* !ALONE_DEBUG */
}

/*---- System Exclusive Messages -----------------------------------------*/
/*--------------------------------------------------------------------------
	Start of System Exclusive Message
		When it is recieved 0xF0, this function is called by midirx.c
--------------------------------------------------------------------------*/
void MidiRxStartOfExclusive(char stream)
{
#ifdef ALONE_DEBUG
	printf("Start of System Exclusive :\n");
#endif /* ALONE_DEBUG */
}

/*--------------------------------------------------------------------------
	Data of System Exclusive Message
		When it is recieved each data byte between 
		0xF0 and 0xF7(or other Status byte. except Real Time Message),
		this function is called by midirx.c
--------------------------------------------------------------------------*/
void MidiRxDataOfExclusive(unsigned char data, char stream)
{
#ifdef ALONE_DEBUG
	printf("%02X ", data);	
#endif /* ALONE_DEBUG */
}

/*--------------------------------------------------------------------------
	End of System Exclusive Message
		When it is recieved 0xF7(or other Status byte. 
		except Real Time Message) during recieving 
		system exclusive message.,
		this function is called by midirx.c
--------------------------------------------------------------------------*/
void MidiRxEndOfExclusive(char stream)
{
#ifdef ALONE_DEBUG
	printf("End of System Exclusive:\n");
#endif /* ALONE_DEBUG */
}

/**** Static Functions ****************************************************/
/*---- Channel Messages --------------------------------------------------*/
/*--------------------------------------------------------------------------
	Note Off Message : 0x8n kk vv
		When it is recieved Note off message completely,
		this function is called by midirx.c
	param:	channel = n = 0 - 15
		noteNumber = kk = 0 - 127
		velocity = vv = 0 - 127
		0 <= stream < NUMOF_MIDIRX_STREAM
	return:	none	
--------------------------------------------------------------------------*/
static void NoteOff(unsigned char channel, unsigned char noteNumber, unsigned char velocity, char stream)
{
#ifdef ALONE_DEBUG
	printf("Note Off: ch=%2x, note number=%02x, velocity=%02x\n", channel, noteNumber, velocity);
#endif /* ALONE_DEBUG */
}

/*--------------------------------------------------------------------------
	Note On Message : 0x9n kk vv
		When it is recieved Note on message completely,
		this function is called by midirx.c
	param:	channel = n = 0 - 15
		noteNumber = kk = 0 - 127
		velocity = vv = 0 - 127
		0 <= stream < NUMOF_MIDIRX_STREAM
	return:	none	
--------------------------------------------------------------------------*/
static void NoteOn(unsigned char channel, unsigned char noteNumber, unsigned char velocity, char stream)
{
#ifdef ALONE_DEBUG
	printf("Note On: ch=%2x, note number=%02x, velocity=%02x\n", channel, noteNumber, velocity);
#endif /* ALONE_DEBUG */
}

/*--------------------------------------------------------------------------
	Polyphonic Key Pressure Message : 0xAn kk vv
		When it is recieved Polyphonic key pressure message completely,
		this function is called by midirx.c
	param:	channel = n = 0 - 15
		noteNumber = kk = 0 - 127
		pressure = vv = 0 - 127
		0 <= stream < NUMOF_MIDIRX_STREAM
	return:	none	
--------------------------------------------------------------------------*/
static void PolyKeyPressure(unsigned char channel, unsigned char noteNumber, unsigned char puressure, char stream)
{
#ifdef ALONE_DEBUG
	printf("Polyphonic Pressure: ch=%2x, note number=%02x, puressure=%02x\n", channel, noteNumber, puressure);
#endif /* ALONE_DEBUG */
}

/*--------------------------------------------------------------------------
	Control Change Message : 0xBn cc vv
		When it is recieved Control Change message completely,
		this function is called by midirx.c
	param:	channel = n = 0 - 15
		controlNumber = cc = 0 - 127
		controlValue = vv = 0 - 127
		0 <= stream < NUMOF_MIDIRX_STREAM
	return:	none	
--------------------------------------------------------------------------*/
static void ControlChange(unsigned char channel, unsigned char controlNumber, unsigned char controlValue, char stream)
{
#ifdef ALONE_DEBUG
	printf("Control Change: ch=%2x, control number=%02x, data=%02x\n", channel, controlNumber, controlValue);
#endif /* ALONE_DEBUG */
}

/*--------------------------------------------------------------------------
	Program Change Message : 0xCn pp
		When it is recieved Program Change message completely,
		this function is called by midirx.c
	param:	channel = n = 0 - 15
		programNumber = pp = 0 - 127
		0 <= stream < NUMOF_MIDIRX_STREAM
		dummy = should igore
	return:	none	
--------------------------------------------------------------------------*/
static void ProgramChange(unsigned char channel, unsigned char programNumber, unsigned char dummy, char stream)
{
#ifdef ALONE_DEBUG
	printf("Program Change: ch=%2x, program number=%02x\n", channel, programNumber);
#endif /* ALONE_DEBUG */
}

/*--------------------------------------------------------------------------
	Channel Pressuer Message : 0xDn vv
		When it is recieved Channel pressure message completely,
		this function is called by midirx.c
	param:	channel = n = 0 - 15
		pressureValue = vv = 0 - 127
		0 <= stream < NUMOF_MIDIRX_STREAM
		dummy = should igore
	return:	none	
--------------------------------------------------------------------------*/
static void ChannelPressure(unsigned char channel, unsigned char pressureValue, unsigned char dummy, char stream)
{
#ifdef ALONE_DEBUG
	printf("Channel Pressure: ch=%2x, puressure=%02x\n", channel, pressureValue);
#endif /* ALONE_DEBUG */
}

/*--------------------------------------------------------------------------
	Pitch Bend Change Message : 0xEn ll mm
		When it is recieved Pitch bend change message completely,
		this function is called by midirx.c
	param:	channel = n = 0 - 15
		lsb = ll = 0 - 127
		msb = mm = 0 - 127
		0 <= stream < NUMOF_MIDIRX_STREAM
	return:	none	
--------------------------------------------------------------------------*/
static void PitchBendChange(unsigned char channel, unsigned char lsb, unsigned char msb, char stream)
{
#ifdef ALONE_DEBUG
	printf("Pitch Bend Change: ch=%2x, bend=%04x\n", channel, (unsigned int)msb<<7 | lsb);
#endif /* ALONE_DEBUG */
}

/*---- System Common Messages ---------------------------------------------*/
/*--------------------------------------------------------------------------
	MTC(MIDI Time Code) Quarter Frame Message : 0xF1 nd
		When it is recieved MTC quarter frame message completely,
		this function is called by midirx.c
	param:	typeValue = nd = 0 - 127
		0 <= stream < NUMOF_MIDIRX_STREAM
		dummy = should igore
	return:	none	
--------------------------------------------------------------------------*/
static void MTCQuarterFrame(unsigned char typeValue, unsigned char dummy, char stream)
{
#ifdef ALONE_DEBUG
	printf("MTC Quarter Frame: type=%2x, value=%04x\n", 0x0f & (typeValue>>4), 0x0f & typeValue);
#endif /* ALONE_DEBUG */
}

/*--------------------------------------------------------------------------
	Song Position Pointer Message : 0xF2 ll hh
		When it is recieved Song position pointer message completely,
		this function is called by midirx.c
	param:	lsb = ll = 0 - 127
		msb = mm = 0 - 127
		0 <= stream < NUMOF_MIDIRX_STREAM
	return:	none	
--------------------------------------------------------------------------*/
static void SongPositionPointer(unsigned char lsb, unsigned char msb, char stream)
{
#ifdef ALONE_DEBUG
	printf("Song Position Pointer: position=%04x\n", (((unsigned int)msb)<<7) | lsb) ;
#endif /* ALONE_DEBUG */
}

/*--------------------------------------------------------------------------
	Song Select Message : 0xF3 ss
		When it is recieved Song select message completely,
		this function is called by midirx.c
	param:	songNumber = ss = 0 - 127
		0 <= stream < NUMOF_MIDIRX_STREAM
		dummy = should igore
	return:	none	
--------------------------------------------------------------------------*/
static void SongSelect(unsigned char songNumber, unsigned char dummy, char stream)
{
#ifdef ALONE_DEBUG
	printf("Song Select: song number=%x\n", songNumber);
#endif /* ALONE_DEBUG */
}

/*--------------------------------------------------------------------------
	Tune Request Message : 0xF6
		When it is recieved Tune request message completely,
		this function is called by midirx.c
	param:	0 <= stream < NUMOF_MIDIRX_STREAM
		dummy0,1 = should igore
	return:	none	
--------------------------------------------------------------------------*/
static void TuneRequest(unsigned char dummy0, unsigned char dummy1, char stream)
{
#ifdef ALONE_DEBUG
	printf("TuneRequest: \n");
#endif /* ALONE_DEBUG */
}

/*--------------------------------------------------------------------------
	Undefined 0xF4 Message : 0xF4
		When it is recieved Undefined 0xF4 message,
		this function is called by midirx.c
	param:	0 <= stream < NUMOF_MIDIRX_STREAM
		dummy0,1 = should igore
	return:	none	
	remark: Normaly, no operation
--------------------------------------------------------------------------*/
static void UndefF4(unsigned char dummy0, unsigned char dummy1, char stream)
{
#ifdef ALONE_DEBUG
	printf("Undefined 0xF4: \n");
#endif /* ALONE_DEBUG */
}

/*--------------------------------------------------------------------------
	Undefined 0xF5 Message : 0xF5
		When it is recieved Undefined 0xF4 message,
		this function is called by midirx.c
	param:	0 <= stream < NUMOF_MIDIRX_STREAM
		dummy0,1 = should igore
	return:	none	
	remark: Normaly, no operation
--------------------------------------------------------------------------*/
static void UndefF5(unsigned char dummy0, unsigned char dummy1, char stream)
{
#ifdef ALONE_DEBUG
	printf("Undefined 0xF5: \n");
#endif /* ALONE_DEBUG */
}

/*---- System Real Time Messages ------------------------------------------*/
/*--------------------------------------------------------------------------
	Timing Clock Message : 0xF8
		When it is recieved Timing Clock message,
		this function is called by midirx.c
	param:	0 <= stream < NUMOF_MIDIRX_STREAM
	return:	none	
--------------------------------------------------------------------------*/
static void TimingClock(char stream)
{
#ifdef ALONE_DEBUG
	printf("Timing Clock:\n");
#endif /* ALONE_DEBUG */
}

/*--------------------------------------------------------------------------
	Start Message : 0xFA
		When it is recieved Start message,
		this function is called by midirx.c
	param:	0 <= stream < NUMOF_MIDIRX_STREAM
	return:	none	
--------------------------------------------------------------------------*/
static void Start(char stream)
{
#ifdef ALONE_DEBUG
	printf("Start:\n");
#endif /* ALONE_DEBUG */
}

/*--------------------------------------------------------------------------
	Continue Message : 0xFB
		When it is recieved Continue message,
		this function is called by midirx.c
	param:	0 <= stream < NUMOF_MIDIRX_STREAM
	return:	none	
--------------------------------------------------------------------------*/
static void Continue(char stream)
{
#ifdef ALONE_DEBUG
	printf("Continue:\n");
#endif /* ALONE_DEBUG */
}

/*--------------------------------------------------------------------------
	Stop Message : 0xFC
		When it is recieved Stop message,
		this function is called by midirx.c
	param:	0 <= stream < NUMOF_MIDIRX_STREAM
	return:	none	
--------------------------------------------------------------------------*/
static void Stop(char stream)
{
#ifdef ALONE_DEBUG
	printf("Stop:\n");
#endif /* ALONE_DEBUG */
}

/*--------------------------------------------------------------------------
	Active Sensing Message : 0xFE
		When it is recieved Active Sensing message,
		this function is called by midirx.c
	param:	0 <= stream < NUMOF_MIDIRX_STREAM
	return:	none	
--------------------------------------------------------------------------*/
static void ActiveSensing(char stream)
{
#ifdef ALONE_DEBUG
	printf("Active Sensing:\n");
#endif /* ALONE_DEBUG */
}

/*--------------------------------------------------------------------------
	System Reset Message : 0xFF
		When it is recieved System reset message,
		this function is called by midirx.c
	param:	0 <= stream < NUMOF_MIDIRX_STREAM
	return:	none	
--------------------------------------------------------------------------*/
static void SystemReset(char stream)
{
#ifdef ALONE_DEBUG
	printf("System Reset:\n");
#endif /* ALONE_DEBUG */
}

/*--------------------------------------------------------------------------
	Undefined 0xF9 Message : 0xF9
		When it is recieved Undefined 0xF9 message,
		this function is called by midirx.c
	param:	0 <= stream < NUMOF_MIDIRX_STREAM
	return:	none	
	remark: Normaly, no operation
--------------------------------------------------------------------------*/
static void UndefF9(char stream)
{
#ifdef ALONE_DEBUG
	printf("System Reset:\n");
#endif /* ALONE_DEBUG */
}

/*--------------------------------------------------------------------------
	Undefined 0xFD Message : 0xFD
		When it is recieved Undefined 0xFD message,
		this function is called by midirx.c
	param:	0 <= stream < NUMOF_MIDIRX_STREAM
	return:	none	
	remark: Normaly, no operation
--------------------------------------------------------------------------*/
static void UndefFD(char stream)
{
#ifdef ALONE_DEBUG
	printf("System Reset:\n");
#endif /* ALONE_DEBUG */
}

/*==== Module Debug ====================================================*/
#ifdef ALONE_DEBUG
int main(int argc, char* argv[])
{
	int stream;
	int data;
	char terminater;

	for(stream = 0; stream < NUMOF_MIDIRX_STREAM; stream++) {
		MidiRxInit(stream);
	}

	while(EOF != (data = getc(stdin))) {
		ungetc(data, stdin);
		MidiRx(0);
	}

	return 0;
}
#endif /* ALONE_DEBUG */

/*==========================================================================
	End
==========================================================================*/
