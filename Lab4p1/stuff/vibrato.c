/*
 * flanger.c
 *
 *  Created on: May 29th, 2019
 *      Author: Zicheng He
 */

#include "vibrato.h"
#include <math.h>
extern int vib_delay;
#define PI 3.14159265358979323846264338327950288419716939937510582

int vib_ii = 0, vib_jj = 0;


short vib_bufL[128], vib_bufR[128];
extern char vibEnable;
char vibEnable = 0;

void vibrato(stereoSample*CodecDataIn, stereoSample* CodecDataOut) {
    if (vibEnable) {
    short xLeft, xRight, yLeft, yRight;
	xLeft  = CodecDataIn->Channel[ 0];
	xRight = CodecDataIn->Channel[ 1];
	
	vib_bufL[vib_ii] = xLeft;
	vib_bufR[vib_ii] = xRight;
	

//#include <stdio.h>
	 int vib_delay; vib_delay = (int) (63.5 * sin(PI * ((double)vib_jj / 1024.0)) + 63.5);
	//printf("%d\n",vib_delay);
	int pos = (128 + vib_ii - vib_delay) % 128;
	//int pos = (128 + vib_ii - vib_delay) % 128;
	
	yLeft = vib_bufL[pos];
	yRight = vib_bufR[pos];
	
	CodecDataOut->Channel[0] = yLeft ;
	CodecDataOut->Channel[1] = yRight;
    vib_ii++;
	if (vib_ii >= 128) vib_ii = 0;
	if (vib_ii % 4 == 0) vib_jj++;
	if (vib_jj >= 2048) vib_jj = 0;
    } else {
        CodecDataOut->ABC = CodecDataIn->ABC;
    }
}
