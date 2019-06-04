/*
 * echo.h
 *
 *  Created on: May 7, 2019
 *      Author: tayl0rh
 */

#ifndef _ECHO_H_
#define _ECHO_H_

#include "../DSP_Config.h"
#include "stereoSample.h"
#include <stdlib.h>

#define Malloc(type,n) (type *)malloc((n)*sizeof(type))
#define Calloc(type,n) (type *)calloc(n,sizeof(type))

void echo_init();
void echo_doShit(stereoSample*CodecDataIn, stereoSample* CodecDataOut
	/*short* echo_bufL, short* echo_bufR*/);

// wtf wrong location.
//float feedback;
//stereoSample* buffer;
//Uint32 ii;
//Uint32 iii; // which is where the output writing location is.

#endif /* _ECHO_H_ */
