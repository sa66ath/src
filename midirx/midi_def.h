/*==========================================================================
	midi_def.h:
==========================================================================*/
#ifndef	_MIDI_DEF_H
#define	_MIDI_DEF_H

/*---- Status ------------------------------------------------------------*/
#define	STATUS_MASK		0x80

#define CHANNEL_MSG_MASK	0xF0
#define	CHANNEL_MASK		0x0F

#define	CHANNEL_MSG		0x80

#define	NOTEOFF_STATUS		0x80
#define	NOTEON_STATUS		0x90
#define	POLYPRESS_STATUS	0xA0
#define	CTRLCHANGE_STATUS	0xB0
#define	PROGCHANGE_STATUS	0xC0
#define	CHPRESS_STATUS		0xD0
#define	PITCHBEND_STATUS	0xE0

#define	SYSTEM_MSG		0xF0

#define	EXCLUSIVE_STATUS	0xF0

#define	SYSTEM_COMMON_MSG	0xF1

#define	MTC_STATUS		0xF1
#define	SONGPOSITION_STATUS	0xF2
#define	SONGSELECT_STATUS	0xF3
#define	UNDEF1_STATUS		0xF4
#define	UNDEF2_STATUS		0xF5
#define	TUNEREQ_STATUS		0xF6
#define	ENDOFEX_STATUS		0xF7

#define	SYSTEM_REALTIME_MSG	0xF8

#define	CLOCK_STATUS		0xF8
#define	UNDEF3_STATUS		0xF9
#define	START_STATUS		0xFA
#define	CONTINUE_STATUS		0xFB
#define	STOP_STATUS		0xFC
#define	UNDEF4_STATUS		0xFD
#define	ACTIVESENS_STATUS	0xFE
#define	RESET_STATUS		0xFF

/*---- Control Change ----------------------------------------------------*/
#define	CC_BANK_MSB		0x00
#define	CC_MODULATION_MSB	0x01
#define	CC_BREATH_MSB		0x02

#define	CC_FOOT_MSB		0x04
#define	CC_PORTAMENT_MSB	0x05
#define	CC_DATA_ENTRY_MSB	0x06
#define	CC_VOLUME_MSB		0x07
#define	CC_BALANCE_MSB		0x08

#define	CC_PAN_MSB		0x0A
#define	CC_EXPRESSION_MSB	0x0B
#define	CC_EFFECT1_MSB		0x0C
#define	CC_EFFECT2_MSB		0x0D

#define	CC_GENERAL1_MSB		0x10
#define	CC_GENERAL2_MSB		0x11
#define	CC_GENERAL3_MSB		0x12
#define	CC_GENERAL4_MSB		0x13

#define	CC_BANK_LSB		0x20
#define	CC_MODULATION_LSB	0x21
#define	CC_BREATH_LSB		0x22

#define	CC_FOOT_LSB		0x24
#define	CC_PORTAMENT_LSB	0x25
#define	CC_DATA_ENTRY_LSB	0x26
#define	CC_VOLUME_LSB		0x27
#define	CC_BALANCE_LSB		0x28

#define	CC_PAN_LSB		0x2A
#define	CC_EXPRESSION_LSB	0x2B
#define	CC_EFFECT1_LSB		0x2C
#define	CC_EFFECT2_LSB		0x2D

#define	CC_GENERAL1_LSB		0x30
#define	CC_GENERAL2_LSB		0x31
#define	CC_GENERAL3_LSB		0x32
#define	CC_GENERAL4_LSB		0x33

#define	CC_HOLD1		0x40
#define	CC_PORTAMENTO		0x41
#define CC_SOSTENUTO		0x42
#define	CC_SOFT_PEDAL		0x43
#define	CC_LEGATO		0x44
#define	CC_HOLD2		0x45
#define	CC_SOUND_CONTROLER1	0x46
#define	CC_RESONANCE		0x47
#define	CC_RELEASE		0x48
#define	CC_ATTACK		0x49
#define	CC_CUTOFF		0x4A
#define	CC_DECAY		0x4B
#define	CC_VIBRATO_RATE		0x4C
#define	CC_VIBRATO_DEPTH	0x4D
#define	CC_VIBRATO_DELAY	0x4E

#define	CC_GENERAL5		0x50
#define	CC_GENERAL6		0x51
#define	CC_GENERAL7		0x52
#define	CC_GENERAL8		0x53
#define	CC_PORTAMENT_CONTROL	0x54

#define	CC_REVERB		0x5B
#define	CC_TREMOLO		0x5C
#define	CC_CHORUS		0x5D
#define	CC_CELESTE		0x5E
#define	CC_PHASER		0x5F
#define	CC_DATA_INC		0x60
#define	CC_DATA_DEC		0x61
#define	CC_NRPN_LSB		0x62
#define	CC_NRPN_MSB		0x63
#define	CC_RPN_LSB		0x64
#define	CC_RPN_MSB		0x65

#define	CC_ALL_SOUND_OFF	0x78
#define	CC_RESET_ALL_SOUND_OFF	0x79
#define	CC_LOCAL_CONTROL	0x7A
#define	CC_ALL_NOTE_OFF		0x7B
#define	CC_OMNI_OFF		0x7C
#define	CC_OMNI_ON		0x7D
#define	CC_MONO_ON		0x7E
#define	CC_POLY_ON		0x7F

/*---- Registered Parameter Number  --------------------------------------*/
#define	RPN_BEND_SENS_MSB	0x00
#define	RPN_BEND_SENS_LSB	0x00

#define	RPN_FINE_TUNE_MSB	0x00
#define	RPN_FINE_TUNE_LSB	0x01

#define	RPN_COARSE_TUNE_MSB	0x00
#define	RPN_COARSE_TUNE_LSB	0x02

#define	RPN_TUNING_PROG_MSB	0x00
#define	RPN_TUNING_PROG_LSB	0x03

#define	RPN_TUNING_BANK_MSB	0x00
#define	RPN_TUNING_BANK_LSB	0x04

#define	RPN_NULL_MSB		0x7F
#define	RPN_NULL_LSB		0x7F

#endif	/* _MIDI_DEF_H */
/*==========================================================================
	End
==========================================================================*/
