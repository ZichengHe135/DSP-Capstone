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
#include <time.h> // time.h header

  
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
int bR[20]; // c vrs
int bL[20];
int bRasm[20]; // asm vrs
int bLasm[20];
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
		// c. fnctn
clock_t  start, stop; // defines the start and stop times
 start = time(0); // get current time (before starting the process)

		for (j = 0; j < 20; j++) {
			bR[j] = 0.0;
			bL[j] = 0.0;
			bRasm[j] = 0.0;
			bLasm[j] = 0.0;
		}
		for (j = 0; j < 20; j++) {
			for (k = 0; k <= 512 - j - 1; k++) {
				bL[j] += (int) bufL[k] * (int) bufL[k + j];
				bR[j] += (int) bufR[k] * (int) bufR[k + j];
			}
		}
	stop = time(0); // get current time (after finishing the process)
	time_t dur = stop-start; // find duration
	printf("Processing time used 4 C ver.: %d s\n",dur); // print the result

	 start = time(0); // get current time (before starting the process)
		autocorr(bufL, bLasm, 512);
		autocorr(bufR, bRasm, 512);
	stop = time(0); // get current time (after finishing the process)
	dur = stop-start; // find duration
	printf("Processing time used 4 ASM ver.: %d s\n",dur); // print the result

		for (iii = 0; iii < 20; iii++) {
			printf("%d left = %d, right = %d\n", iii, bL[iii], bR[iii]);
			printf("%d left = %d, right = %d (asm)\n", iii, bLasm[iii], bRasm[iii]);
		}
//		for (iii = 0; iii < 512; iii++) {
//			printf("%d left = %d, right = %d\n", iii, bufL[iii], bufR[iii]);
//		}
	}

	CodecDataOut.Channel[LEFT] = xLeft;
	CodecDataOut.Channel[RIGHT] = xRight;
	/* end your code here */

	WriteCodecData(CodecDataOut.ABC);		// send output data to  port
}


