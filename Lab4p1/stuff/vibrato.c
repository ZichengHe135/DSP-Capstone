/*
 * flanger.c
 *
 *  Created on: May 29th, 2019
 *      Author: Zicheng He
 */

#include "vibrato.h"
#include <math.h>
extern int vib_delay;
#define PI 3.14159265

int vib_ii = 0, vib_jj = 0;


short vib_bufL[720], vib_bufR[720];

void vibrato(stereoSample*CodecDataIn, stereoSample* CodecDataOut) {
	short xLeft, xRight, yLeft, yRight;
	xLeft  = CodecDataIn->Channel[ 0];
	xRight = CodecDataIn->Channel[ 1];
	
	vib_bufL[vib_ii] = xLeft;
	vib_bufR[vib_ii] = xRight;
	
	vib_ii++;
#include <stdio.h>
	 int vib_delay; vib_delay = (int) (360.0 * sin(PI * ((double)vib_jj / 1024.0)) + 360);
	//printf("%d\n",vib_delay);
	int left_pos = (720 + vib_ii - vib_delay) % 720;
	int right_pos = (720 + vib_ii - vib_delay) % 720;
	
	yLeft = vib_bufL[left_pos];
	yRight = vib_bufR[right_pos];
	
	CodecDataOut->Channel[0] = yLeft + xLeft;
	CodecDataOut->Channel[1] = yRight+ xRight;
	if (vib_ii > 719) vib_ii = 0;
	if (vib_ii % 0x10 == 0) vib_jj++;
	if (vib_jj > 2048) vib_jj = 0;
	return;
}
