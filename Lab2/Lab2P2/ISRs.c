// Welch, Wright, & Morrow, 
// Real-time Digital Signal Processing, 2011

///////////////////////////////////////////////////////////////////////
// Filename: ISRs.c
//
// Synopsis: Interrupt service routine for codec data transmit/receive
//
///////////////////////////////////////////////////////////////////////

#include "DSP_Config.h"
#include <stdio.h>

  
// Data is received as 2 16-bit words (left/right) packed into one
// 32-bit word.  The union allows the data to be accessed as a single 
// entity when transferring to and from the serial port, but still be 
// able to manipulate the left and right channels independently.

#define LEFT  0
#define RIGHT 1
#define L 1024

volatile union {
	Uint32 ABC;
	Int16 Channel[2];
} CodecDataIn, CodecDataOut;


/* add any global variables here */
short bufL[L];
short bufR[L];
short resL[L];
short resR[L];
int ii = 0;
int iii = 0;
int ij = 0;


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

	int flag1 = ReadSwitches() % 2;  // use SW 5 to control start of sampling
	int flag2 = ReadSwitches() % 4 / 2;  // use SW 6 to control playing reverse or not

	if (flag1) {
		if (ii < L) {
			bufL[ii] = xLeft;
			bufR[ii] = xRight;
		}
		ii++;
	} else {
		ii = 0;
	}


	if (ii == L && flag1) {
		reversefunc(bufL, resL, L);
		reversefunc(bufR, resR, L);
		//for (iii = 0; iii < L; iii++) {
		//	printf("left=%d, left reversed=%d, at %d\n", bufL[iii], resL[iii], iii);
		//	printf("right=%d, right reversed=%d, at %d\n", bufR[iii], resR[iii], iii);
		//}

	}

	if (ii < L) {
		CodecDataOut.Channel[LEFT] = 0;
		CodecDataOut.Channel[RIGHT] = 0;
	} else if (flag2) {
		CodecDataOut.Channel[LEFT] = bufL[ij];
		CodecDataOut.Channel[RIGHT] = bufR[ij];
	} else {
		CodecDataOut.Channel[LEFT] = resL[ij];
		CodecDataOut.Channel[RIGHT] = resR[ij];
	}

	ij++;
	if (ij >= L) ij = 0;
	/* end your code here */

	WriteCodecData(CodecDataOut.ABC);		// send output data to  port
}

