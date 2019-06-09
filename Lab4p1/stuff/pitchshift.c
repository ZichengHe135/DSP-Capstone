/*
 * pitchshift.c
 *
 *  Created on: May 7, 2019
 *      Author: tayl0rh
 *  based on the code from Lab2 Problem4
 */

#include "pitchshift.h"
//#include "../DSP_Config.h"
#include <stdlib.h>

#define BUFFER 1024
#define HBUFFER 512
#define HBUFFERf 512.0

int pitchShift_ii = 0;
int pitchShift_delay = 0;
short pitchShift_bufL[BUFFER];
short pitchShift_bufR[BUFFER];

extern char psEnableHiLow;
char psEnableHiLow = 0;

void pitchShift(stereoSample*CodecDataIn, stereoSample* CodecDataOut) {
	short xLeft, xRight, yLeft, yRight;
	xLeft  = CodecDataIn->Channel[ 0];
	xRight = CodecDataIn->Channel[ 1];


	if (psEnableHiLow & 1) {
		// SW5 up, do pitch shifting
	    double gain = abs(HBUFFERf - pitchShift_delay) / HBUFFERf;  // Triangle wave
		int iA, iB;

		if (!(psEnableHiLow & 2)) {
			// SW6 up, pitch up
			iA = (pitchShift_ii + pitchShift_delay) % BUFFER;
			iB = (pitchShift_ii + pitchShift_delay + HBUFFER) % BUFFER;
		} else {
			// SW6 down, pitch down
			iA = (pitchShift_ii - pitchShift_delay + BUFFER) % BUFFER;
			iB = (pitchShift_ii - pitchShift_delay + HBUFFER) % BUFFER;
 		}
		yLeft = (1 - gain) * pitchShift_bufL[iA] + gain * pitchShift_bufL[iB];
		yRight = (1 - gain) * pitchShift_bufR[iA] + gain * pitchShift_bufR[iB];
	} else {
		// SW5 down, do nothing
		yLeft = xLeft;
		yRight = xRight;
	}

	pitchShift_bufL[pitchShift_ii] = xLeft;
	pitchShift_bufR[pitchShift_ii] = xRight;

	pitchShift_ii++;
	if (pitchShift_ii % 2) pitchShift_delay++;

	CodecDataOut->Channel[0] = yLeft;
	CodecDataOut->Channel[1] = yRight;
	if (pitchShift_ii >= BUFFER) pitchShift_ii = 0;
	if (pitchShift_delay >= BUFFER) pitchShift_delay = 0;
	return;
}
