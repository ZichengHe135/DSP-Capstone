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
	float xLeft, xRight, yLeft, yRight;


 	if(CheckForOverrun())					// overrun error occurred (i.e. halted DSP)
		return;								// so serial port is reset to recover

  	CodecDataIn.ABC = ReadCodecData();		// get input data samples
	
	/* add your code starting here */
  	xLeft  = CodecDataIn.Channel[ LEFT];
	xRight = CodecDataIn.Channel[ RIGHT];

	yLeft  = xLeft;
	yRight = xRight;

	CodecDataOut.Channel[LEFT] = yLeft;
	CodecDataOut.Channel[RIGHT] = yRight;

	if (ReadSwitches() % 8 / 2 == 0) {  // up, up
		WriteLEDs(3);
	} else if (ReadSwitches() % 8 / 2 == 1) {  // up, down
		CodecDataOut.Channel[RIGHT] = 0;
		WriteLEDs(2);
	} else if (ReadSwitches() % 8 / 2 == 2) {  // down, up
		CodecDataOut.Channel[LEFT] = 0;
		WriteLEDs(1);
	} else {  // down, down
		CodecDataOut.Channel[LEFT] = 0;
		CodecDataOut.Channel[RIGHT] = 0;
		WriteLEDs(0);
	}
	/* end your code here */

	WriteCodecData(CodecDataOut.ABC);		// send output data to  port
}

