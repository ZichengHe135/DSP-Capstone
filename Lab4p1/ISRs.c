// Welch, Wright, & Morrow, 
// Real-time Digital Signal Processing, 2011

///////////////////////////////////////////////////////////////////////
// Filename: ISRs.c
//
// Synopsis: Interrupt service routine for codec data transmit/receive
//
///////////////////////////////////////////////////////////////////////

#include "DSP_Config.h"
#include <stdlib.h>
//#include "stuff/echo.h"
//#include "stuff/reverb.h"
#include "stuff/pitchshift.h"
//#include "stuff/osc.h"
  
// Data is received as 2 16-bit words (left/right) packed into one
// 32-bit word.  The union allows the data to be accessed as a single 
// entity when transferring to and from the serial port, but still be 
// able to manipulate the left and right channels independently.

#define LEFT  0
#define RIGHT 1

//typedef volatile union {
//	Uint32 ABC;
//	Int16 Channel[2];
//} stereoSample;
//float feedback = 0;
//Uint32 ii = 0;
//Uint32 iii = 0; // which is where the output writing location is.
//Uint32	delay = 64;

#include "stuff/synth.hpp"


//typedef volatile union {
//	Uint32 ABC;
//	Int16 Channel[2];
//} stereoSample;


stereoSample CodecDataIn, CodecDataOut;


/* add any global variables here */

short pitchShift_bufL[720];
short pitchShift_bufR[720];
//short echo_bufL[32768] = {0}; //buffer[]
//short echo_bufR[32768] = {0};
#include "stuff/synth.hpp"
interrupt void Codec_ISR()
///////////////////////////////////////////////////////////////////////
// Purpose:   Codec interface interrupt service routine  
//
// Input:     None
//
// Returns:   Nothing
//
// Calls:     CheckForOverrun, ReadCodecData, WriteCodecData
//
// Notes:     None
///////////////////////////////////////////////////////////////////////
{                    
	/* add any local variables here */



 	if(CheckForOverrun())					// overrun error occurred (i.e. halted DSP)
		return;								// so serial port is reset to recover

	CodecDataIn.ABC = ReadCodecData();		// get input data samples
	
	/* add your code starting here */

	CodecDataIn.Channel[0] = SYNTH_Tick();
	pitchShift(&CodecDataIn, &CodecDataOut, pitchShift_bufL, pitchShift_bufR); // working
	//echo_doShit(&CodecDataIn, &CodecDataOut, echo_bufL, echo_bufR);
	//reverb_doShit(&CodecDataIn, &CodecDataOut);

	//CodecDataOut = oscillators();
	/* end your code here */

	WriteCodecData(CodecDataOut.ABC);		// send output data to  port
}

