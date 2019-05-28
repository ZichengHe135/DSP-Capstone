/*
 * echo.c
 *
 *  Created on: May 7, 2019
 *      Author: tayl0rh
 */
#include "echo.h"
#define MAX_SIZE 32768 // of buffer in stereo smp.s
#include "pitchshift.h"
#include "../DSP_Config.h"
#include <stdlib.h>

/* add any global variables here */
float feedback = 0;
Uint32 ii = 0;
Uint32 iii = 0; // which is where the output writing location is.

int delay = MAX_SIZE;




int echo_ii = 0;
int echo_delay = 8192;

void   echo_init() {

	feedback = 0;
	delay = MAX_SIZE;
	ii = 0;
	iii = 0; // newPhase=0
}
void   echo_doShit(stereoSample*CodecDataIn, stereoSample* CodecDataOut,
				   short* echo_bufL, short* echo_bufR) {
		short xLeft, xRight, yLeft, yRight;
		xLeft  = CodecDataIn->Channel[ 0];
		xRight = CodecDataIn->Channel[ 1];
		if (ReadSwitches() & 4) { // != 0
			// SW7 down, do nothing
			yLeft = xLeft;
			yRight = xRight;
		} else {
			// SW7 up, do echo
			int iA, iB;

//			if (flag2 == 0) {
//				// SW6 up, pitch up
//				iA = (echo_ii + echo_delay) % 720;
//				iB = (echo_ii + echo_delay + 360) % 720;
//			} else {
//				// SW6 down, pitch down
				iA = (echo_ii - echo_delay + MAX_SIZE) % MAX_SIZE;
				iB = (echo_ii );//- echo_delay + MAX_SIZE/2) % MAX_SIZE; // make this channel one have the non offset one
//			}
			yLeft = echo_bufL[iA] + xLeft; //temp mix w dry do this later
			yRight = echo_bufR[iB] + xRight;

		}

		echo_bufL[echo_ii] = (xLeft>>1) + echo_bufL[echo_ii] * 0.5; //dec. vol. b4 put in buffer for headroom
		echo_bufR[echo_ii] = (xRight>>1) + echo_bufR[echo_ii] * 0.5;

		echo_ii++;
		//if (echo_ii >>4) echo_delay++;

		CodecDataOut->Channel[0] = yLeft;
		CodecDataOut->Channel[1] = yRight;
		if (echo_ii >= delay) echo_ii = 0;
		if (echo_delay >= delay) echo_delay = 0;
		return;
}
void   echo_reset(Uint32 newDelay, float newPhase) {
	delay = newDelay;
	if(ii >= delay) ii = 0;

	iii = (ii + (int) (newPhase * delay)) % delay;
}
