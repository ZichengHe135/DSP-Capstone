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
  
// Data is received as 2 16-bit words (left/right) packed into one
// 32-bit word.  The union allows the data to be accessed as a single 
// entity when transferring to and from the serial port, but still be 
// able to manipulate the left and right channels independently.

#define LEFT  0
#define RIGHT 1

volatile union {
	Uint32 ABC;
	Int16 Channel[2];
} CodecDataIn, CodecDataOut;


/* add any global variables here */
int ii = 0;
int delay = 0;
short bufL[720];
short bufR[720];

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
	short xLeft, xRight, yLeft, yRight;


 	if(CheckForOverrun())					// overrun error occurred (i.e. halted DSP)
		return;								// so serial port is reset to recover

  	CodecDataIn.ABC = ReadCodecData();		// get input data samples
	
	/* add your code starting here */
  	xLeft  = CodecDataIn.Channel[ LEFT];
	xRight = CodecDataIn.Channel[ RIGHT];
	int flag1 = ReadSwitches() % 2;
	int flag2 = ReadSwitches() % 4 /2;


	if (flag1 == 0) {
		// SW5 up, do pitch shifting
		double gain = abs(360 - delay) / 360.0;
		int iA, iB;

		if (flag2 == 0) {
			// SW6 up, pitch up
			iA = (ii + delay) % 720;
			iB = (ii + delay + 360) % 720;
		} else {
			// SW6 down, pitch down
			iA = (ii - delay + 720) % 720;
			iB = (ii - delay + 360) % 720;
 		}
		yLeft = (1 - gain) * bufL[iA] + gain * bufL[iB];
		yRight = (1 - gain) * bufR[iA] + gain * bufR[iB];
	} else {
		// SW5 down, do nothing
		yLeft = xLeft;
		yRight = xRight;
	}

	bufL[ii] = xLeft;
	bufR[ii] = xRight;

	ii++;
	if (ii % 2) delay++;

	CodecDataOut.Channel[LEFT] = yLeft;
	CodecDataOut.Channel[RIGHT] = yRight;
	if (ii > 719) ii = 0;
	if (delay > 719) delay = 0;

	/* end your code here */

	WriteCodecData(CodecDataOut.ABC);		// send output data to  port
}

