// Welch, Wright, & Morrow, 
// Real-time Digital Signal Processing, 2011

///////////////////////////////////////////////////////////////////////
// Filename: ISRs.c
//
// Synopsis: Interrupt service routine for codec data transmit/receive
//
///////////////////////////////////////////////////////////////////////

#include "DSP_Config.h" 
  
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
short bufL[800];
short bufR[800];

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


	if (ReadSwitches() % 2 == 0) {
		// SW5 up
		int flag = ReadSwitches() % 8 / 2;  // SW6 and 7
		int old;
		if (flag == 0) {
			// up, up, delay by 200
			old = (ii + 600) % 800;
		} else if (flag == 1) {
			// up, down, delay by 400
			old = (ii + 400) % 800;
		} else if (flag == 2) {
			// down, up, delay by 600
			old = (ii + 200) % 800;
		} else {
			// down, down, delay by 800
			old = ii;
		}
		yLeft = bufL[old];
		yRight = bufR[old];
	} else {
		// SW5 down, do nothing
		yLeft = 0;
		yRight = 0;
	}

	bufL[ii] = xLeft;
	bufR[ii] = xRight;

	ii++;

	CodecDataOut.Channel[LEFT] = yLeft + xLeft;
	CodecDataOut.Channel[RIGHT] = yRight + xRight;
	if (ii > 799) ii = 0;

	/* end your code here */

	WriteCodecData(CodecDataOut.ABC);		// send output data to  port
}

