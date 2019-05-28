/*
 * echo.h
 *
 *  Created on: May 7, 2019
 *      Author: tayl0rh
 */

#ifndef STUFF_PS_H_
#define STUFF_PS_H_

#include <stdlib.h>
#include "../DSP_Config.h"
#include "stereoSample.h"

void   pitchShift(stereoSample* CodecDataIn, stereoSample* CodecDataOut, short* pitchShift_bufL, short* pitchShift_bufR);

#endif /* STUFF_PS_H_ */
