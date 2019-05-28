/*
 * echo.h
 *
 *  Created on: May 7, 2019
 *      Author: tayl0rh
 */

#ifndef ECHO_H_
#define ECHO_H_

#include "../DSP_Config.h"
#include "stereoSample.h"
#include <stdlib.h>


#define Malloc(type,n) (type *)malloc((n)*sizeof(type))
#define Calloc(type,n) (type *)calloc(n,sizeof(type))



void   reverb_init(float gn, int d);
void   reverb_doShit(stereoSample*CodecDataIn, stereoSample* CodecDataOut);

// wtf wrong location.
//float feedback;
//stereoSample* buffer;
//Uint32 ii;
//Uint32 iii; // which is where the output writing location is.

#endif /* STUFF_ECHO_H_ */
