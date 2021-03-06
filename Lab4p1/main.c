// Welch, Wright, & Morrow, 
// Real-time Digital Signal Processing, 2011
 
///////////////////////////////////////////////////////////////////////
// Filename: main.c
//
// Synopsis: Main program file for demonstration code
//
///////////////////////////////////////////////////////////////////////

#include "DSP_Config.h"
#include <stdio.h>
#include "stuff/echo.h"
#include "stuff/reverb.h"
#include "stuff/synth.hpp"
//#include <libtst.h>
// void Codec_ISR();
int main()
{

	// initialize DSP board

  	echo_init();
  	reverb_init(0.875, 32768/8); // do /2 for weird stuff
  	//printf("sdfg\n");
  	SYNTH_Init();
	// call StartUp for application specific code
	// defined in each application directory
	StartUp();
	unsigned short i;
	for( i = 1; i != 0; i++);
	DSP_Init();
	//int t = Z4testi(5);
	// main stalls here, interrupts drive operation
  	while(1) {
  	  SYNTH_UpdateSettings();
  	//Codec_ISR();
  	  //printf("fuck yeah, this is the 1st ever in the universe ELF 4mat rt-dsp shit with a c++14 compiler\n");
  	}
}


