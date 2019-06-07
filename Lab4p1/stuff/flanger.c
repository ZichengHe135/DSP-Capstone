/*
 * flanger.c
 *
 *  Created on: May 29th, 2019
 *      Author: Zicheng He
 */

#include "flanger.h"
#include <math.h>
extern int fla_delay;
#define PI 3.14159265

int fla_ii = 0, fla_jj = 0;


short fla_bufL[128], fla_bufR[128];

void flangerShift(stereoSample*CodecDataIn, stereoSample* CodecDataOut) {
	short xLeft, xRight, yLeft, yRight;
	xLeft  = CodecDataIn->Channel[ 0];
	xRight = CodecDataIn->Channel[ 1];
	
	fla_bufL[fla_ii] = xLeft;
	fla_bufR[fla_ii] = xRight;
	
	fla_ii++;
//#include <stdio.h>
	 int fla_delay; fla_delay = (int) (64.0 * sin(PI * ((double)fla_jj / 1024.0)) + 64);
	//printf("%d\n",fla_delay);
	int left_pos = (128 + fla_ii - fla_delay) % 128;
	int right_pos = (128 + fla_ii - fla_delay) % 128;
	
	yLeft = fla_bufL[left_pos];
	yRight = fla_bufR[right_pos];
	
	CodecDataOut->Channel[0] = yLeft + xLeft;
	CodecDataOut->Channel[1] = yRight+ xRight;
	if (fla_ii >= 128) fla_ii = 0;
	if (fla_ii % 0x40 == 0) fla_jj++;
	if (fla_jj >= 2048) fla_jj = 0;
	return;
}
