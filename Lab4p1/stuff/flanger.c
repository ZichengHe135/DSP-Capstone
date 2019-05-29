// Author:  Zicheng He
// Date:    May 29th 2019
// File:    flanger.c
//

#include "flanger.h"
#include <math.h>

#define PI 3.14159265

int fla_ii = 0;

void flangerShift(stereoSample*CodecDataIn, stereoSample* CodecDataOut, short* fla_bufL, short* fla_bufR) {
	short xLeft, xRight, yLeft, yRight;
	xLeft  = CodecDataIn->Channel[ 0];
	xRight = CodecDataIn->Channel[ 1];
	
	fla_bufL[fla_ii] = xLeft;
	fla_bufR[fla_ii] = xRight;
	
	fla_ii++;
	
	int fla_delay = (int) (360 * sin(PI * (fla_ii / 360.0)) + 360);
	
	int left_pos = (720 + fla_ii - fla_delay) % 720;
	int right_pos = (720 + fla_ii - fla_delay) % 720;
	
	yLeft = fla_bufL[left_pos];
	yRight = fla_bufR[right_pos];
	
	CodecDataOut->Channel[0] = yLeft;
	CodecDataOut->Channel[1] = yRight;
	if (fla_ii > 719) pitchShift_ii = 0;
	
	return;
}
