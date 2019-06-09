/*
 * flanger.c
 *
 *  Created on: May 29th, 2019
 *      Author: Zicheng He
 */

#include "flanger.h"
#include <math.h>
#include <assert.h>
#include <stdio.h>
extern int fla_delay;
#define PI 3.14159265358979323846264338327950288419716939937510582

int fla_ii = 0, fla_jj = 0;


short fla_bufL[128], fla_bufR[128];
extern char flangerEnable;
char flangerEnable = 0;

void flanger(stereoSample*CodecDataIn, stereoSample* CodecDataOut) {
    if (flangerEnable) {
	short xLeft, xRight, yLeft, yRight;
	xLeft  = CodecDataIn->Channel[ 0];
	xRight = CodecDataIn->Channel[ 1];
	
	fla_bufL[fla_ii] = xLeft;
	fla_bufR[fla_ii] = xRight;
	

//#include <stdio.h>
	 int fla_delay; fla_delay = (int) (63.5 * sin(PI * ((double)fla_jj / 1024.0)) + 63.5);
	//printf("%d\n",fla_delay);
	int pos = (128 + fla_ii - fla_delay) % 128;
//	int right_pos = (128 + fla_ii - fla_delay) % 128;
//	if(pos <= -1 || pos >= 128 || fla_ii >= 128 || fla_ii <= 0){
//#pragma RETAIN(noonecares)
//	     int noonecares = 62432;
//	     yLeft = fla_bufL[pos];
//	}
	yLeft = fla_bufL[pos];
	yRight = fla_bufR[pos];
	
	CodecDataOut->Channel[0] = yLeft + xLeft;
	CodecDataOut->Channel[1] = yRight+ xRight;
	fla_ii++;
	if (fla_ii >= 128) fla_ii = 0;
	if (fla_ii % 0x40 == 0) fla_jj++;
	if (fla_jj >= 2048) fla_jj = 0; // this is for more precision maybe should be float.
    } else {
        CodecDataOut->ABC = CodecDataIn->ABC;
    }
}
