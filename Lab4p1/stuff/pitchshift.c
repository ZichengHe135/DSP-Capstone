/*
 * pitchshift.c
 *
 *  Created on: May 7, 2019
 *      Author: tayl0rh
 *  based on the code from Lab2 Problem4
 */

#include "pitchshift.h"
#include "../DSP_Config.h"
#include <stdlib.h>

int pitchShift_ii = 0;
int pitchShift_delay = 0;


void pitchShift(stereoSample*CodecDataIn, stereoSample* CodecDataOut, short* pitchShift_bufL, short* pitchShift_bufR) {
	short xLeft, xRight, yLeft, yRight;
	xLeft  = CodecDataIn->Channel[ 0];
	xRight = CodecDataIn->Channel[ 1];
	int flag1 = ReadSwitches() % 2;
	int flag2 = ReadSwitches() % 4 /2;


	if (flag1 == 0) {
		// SW5 up, do pitch shifting
		double gain = abs(360 - pitchShift_delay) / 360.0;
		int iA, iB;

		if (flag2 == 0) {
			// SW6 up, pitch up
			iA = (pitchShift_ii + pitchShift_delay) % 720;
			iB = (pitchShift_ii + pitchShift_delay + 360) % 720;
		} else {
			// SW6 down, pitch down
			iA = (pitchShift_ii - pitchShift_delay + 720) % 720;
			iB = (pitchShift_ii - pitchShift_delay + 360) % 720;
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
	if (pitchShift_ii > 719) pitchShift_ii = 0;
	if (pitchShift_delay > 719) pitchShift_delay = 0;
	return;
}
