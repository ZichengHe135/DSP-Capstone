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
#define L 512

volatile union {
	Uint32 ABC;
	Int16 Channel[2];
} CodecDataIn, CodecDataOut;


/* add any global variables here */
short bufL[512];
short bufR[512];
short bR[20];
short bL[20];
short bRasm[20];
short bLasm[20];
int ii = 0;
int k = 0;
int j = 0;
int iii = 0;

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
	//int flag2 = ReadSwitches() % 4 / 2;  // use SW 6 to control playing reverse or not
	if (flag1) {
		if (ii < 512) {
			bufL[ii] = xLeft;
			bufR[ii] = xRight;
		}
		ii++;
	} else {
		ii = 0;
	}


	if (ii == 512 && flag1) {
		for (j = 0; j < 20; j++) {
			bR[j] = 0;
			bL[j] = 0;
			bRasm[j] = 0;
			bLasm[j] = 0;
		}
		for (j = 0; j < 20; j++) {
			for (k = 0; k <= 512 - j - 1; k++) {
				bL[j] += bufL[k] * bufL[k + j];
				bR[j] += bufR[k] * bufR[k + j];
			}
		}
		autocorr(bufL, bLasm, 512);
		autocorr(bufR, bRasm, 512);
		for (iii = 0; iii < 20; iii++) {
			printf("%d left = %d, right = %d\n", iii, bL[iii], bR[iii]);
			printf("%d left = %d, right = %d (asm)\n", iii, bLasm[iii], bRasm[iii]);
		}

	}

	CodecDataOut.Channel[LEFT] = xLeft;
	CodecDataOut.Channel[RIGHT] = xRight;
	/* end your code here */

	WriteCodecData(CodecDataOut.ABC);		// send output data to  port
}


