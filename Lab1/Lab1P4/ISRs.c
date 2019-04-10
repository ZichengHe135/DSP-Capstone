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
short sinewave[20] = {0, 309, 588, 809, 951, 1000, 951, 809, 588, 309, 0, -309, -588, -809, -951, -1000, -951, -809, -588, -309};

extern int alpha;
extern int beta;
extern int omega;
extern int GUI_OUT[20];

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
  	int temp = 0;
  	ii++;
  	int ii1 = ii * 2 % 20;
  	int ii2 = ii * 3 % 20;
  	int ii3 = ii * 5 % 20;

  	CodecDataOut.Channel[ LEFT] = 0;
	temp += alpha * sinewave[ii1];
	temp += beta * sinewave[ii2];
	temp += omega * sinewave[ii3];
	if (ii > 19) ii = 0;

	CodecDataOut.Channel[RIGHT] = temp;
	GUI_OUT[ii] =  temp;
	/* end your code here */

	WriteCodecData(CodecDataOut.ABC);		// send output data to  port
}

