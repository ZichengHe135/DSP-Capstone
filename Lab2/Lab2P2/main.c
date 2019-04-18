// Welch, Wright, & Morrow, 
// Real-time Digital Signal Processing, 2011
 
///////////////////////////////////////////////////////////////////////
// Filename: main.c
//
// Synopsis: Main program file for demonstration code
//
///////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include "DSP_Config.h"   

int main()
{    
	
	// initialize DSP board
  	DSP_Init();

	// call StartUp for application specific code
	// defined in each application directory
	StartUp();
	
	// main stalls here, interrupts drive operation
	/*
	short ans[1024];
	short ex[1024];
	int ii;
	for (ii = 0; ii < 1024; ii++) {
		ex[ii] = ii;
	}
	reversefunc(ex, ans, 1024);
	for (ii = 0; ii < 1024; ii++) {
		printf("%d, %d", ex[ii], ans[ii]);
	}*/

	while(1) {
  	}   
}


