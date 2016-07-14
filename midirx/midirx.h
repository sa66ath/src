/*==========================================================================
	midirx.h: MIDI RX Routines
		Be sure initializing MIDI RX hardware and calling MidiRxInit() 
		before calling MidiRx().
		Don't modify this file other than NUMOF_MIDIRX_STREAM.
		And don't modify midirx.c .
		You can modify content of functions in midirx_proc.c .
	
					Shoichi Ikeda	Oct. 10th 2004	
==========================================================================*/
#ifndef _MIDIRX_H
#define _MIDIRX_H

/**** Includes ************************************************************/

/**** Definitions *********************************************************/
#define	NUMOF_MIDIRX_STREAM	3

/**** Global Function's Prototypes ****************************************/
#ifdef	__cplusplus
extern C {
#endif	/* __cplusplus */

extern void MidiRx(char stream);
extern void MidiRxInit(char stream);

#ifdef	__cplusplus
}
#endif	/* __cplusplus */

#endif /* _MIDIRX_H */
/*==========================================================================
	End
==========================================================================*/
