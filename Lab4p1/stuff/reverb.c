/*
 * echo.c
 *
 *  Created on: May 7, 2019
 *      Author: tayl0rh
 */
#include "echo.h"
#define MAX_SIZE 4096 // of buffer in stereo smp.s
#include "pitchshift.h"
#include "../DSP_Config.h"
#include <stdlib.h>

/* add any global variables here */
float gain = 0.5;
Uint32 jj1, jj2, jj3, jj4;// = 0;
Uint32 jjj = 0; // which is where the output writing location is.

int delay1 = MAX_SIZE;int delay2 = MAX_SIZE;int delay3 = MAX_SIZE;int delay4 = MAX_SIZE;

//y not in .h
short revrb_bufL1[4096] = {0}; //buffer[]
short revrb_bufR1[4096] = {0};
short revrb_bufL2[4096] = {0}; //buffer[]
short revrb_bufR2[4096] = {0};
short revrb_bufL3[4096] = {0}; //buffer[]
short revrb_bufR3[4096] = {0};
short revrb_bufL4[4096] = {0}; //buffer[]
short revrb_bufR4[4096] = {0};


Uint32 jj = 0;
int reverb_delay = 0;

void   reverb_init(float gn, int d) {

	gain = gn;
	delay1 = d*(4/4);
	delay2 = d*(3.3/4);
	delay3 = d*(2.9/4);
	delay4 = d*(1.7/4);
	jj1 = 0;
	jj2 = 0;
	jj3 = 0;
	jj4 = 0;
	//jjj = 0; // newPhase=0
}
void   reverb_doShit(stereoSample*CodecDataIn, stereoSample* CodecDataOut) {
		short xLeft, xRight, yLeft, yRight, yLeft2, yRight2, yLeft3, yRight3, yLeft4, yRight4;
		if (ReadSwitches() & 4) { // != 0
			// SW7 down, do nothing
		    CodecDataOut->Channel[0] = CodecDataIn->Channel[0];
		    CodecDataOut->Channel[1] = CodecDataIn->Channel[1];
		} else {
			// SW7 up, do echo
	        xLeft  = CodecDataIn->Channel[ 0] >> 2; // /4 b/c
	        xRight = CodecDataIn->Channel[ 1] >> 2;

			int iA, iB;

//			if (flag2 == 0) {
//				// SW6 up, pitch up
//				iA = (jj + reverb_delay) % 720;
//				iB = (jj + reverb_delay + 360) % 720;
//			} else {
//				// SW6 down, pitch down
				iA = (jj1 - reverb_delay + MAX_SIZE) % MAX_SIZE;
				iB = (jj1 );//- reverb_delay + MAX_SIZE/2) % MAX_SIZE; // make this channel one have the non offset one
//			}
			yLeft = revrb_bufL1[jj1] + (short) ((float)xLeft * -1.0 *gain); //temp mix w dry do this later
			yRight = revrb_bufR1[jj1] + (short) ((float)xRight * -1.0 * gain);
			//copying
			yLeft2 = revrb_bufL2[jj2] + (short) ((float)xLeft * -1.0 *gain); //temp mix w dry do this later
			yRight2 = revrb_bufR2[jj2] + (short) ((float)xRight * -1.0 * gain);
			yLeft3 = revrb_bufL3[jj3] + (short) ((float)xLeft * -1.0 *gain); //temp mix w dry do this later
			yRight3 = revrb_bufR3[jj3] + (short) ((float)xRight * -1.0 * gain);
			yLeft4 = revrb_bufL4[jj4] + (short) ((float)xLeft * -1.0 *gain); //temp mix w dry do this later
			yRight4 = revrb_bufR4[jj4] + (short) ((float)xRight * -1.0 * gain);



		revrb_bufL1[jj1] = (short) ((float)xLeft+ ((float)yLeft * gain)); //dec. vol. b4 put in buffer for headroom
		revrb_bufR1[jj1] = (short)((float)xRight+ ((float)yRight * gain));

		revrb_bufL2[jj2] = (short) ((float)xLeft+ ((float)yLeft2 * gain)); //dec. vol. b4 put in buffer for headroom
		revrb_bufR2[jj2] = (short)((float)xRight+ ((float)yRight2 * gain));
		revrb_bufL3[jj3] = (short) ((float)xLeft+ ((float)yLeft3 * gain)); //dec. vol. b4 put in buffer for headroom
		revrb_bufR3[jj3] = (short)((float)xRight+ ((float)yRight3 * gain));
		revrb_bufL4[jj4] = (short) ((float)xLeft+ ((float)yLeft4 * gain)); //dec. vol. b4 put in buffer for headroom
		revrb_bufR4[jj4] = (short)((float)xRight+ ((float)yRight4 * gain));

		jj1++;jj2++;jj3++;jj4++;
		//if (jj >>4) reverb_delay++;

		CodecDataOut->Channel[0] = yLeft+yLeft2+yLeft3+yLeft4;
		CodecDataOut->Channel[1] = yRight+yRight2+yRight3+yRight4;
		if (jj1 >= delay1) jj1 = 0;if (jj2 >= delay2) jj2 = 0;if (jj3 >= delay3) jj3 = 0;if (jj4 >= delay4) jj4 = 0;
	//	if (reverb_delay >= delayy) reverb_delay = 0;
		}
}
void   reverb_reset(Uint32 newDelay, float newPhase) {
	delay1 = newDelay;
	if(jj1 >= delay1) jj1 = 0;

	//jjj = (jj + (int) (newPhase * delayy)) % delayy;
}
