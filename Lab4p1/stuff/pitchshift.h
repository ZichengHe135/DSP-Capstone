/*
 * pitchshift.h
 *
 *  Created on: May 7, 2019
 *      Author: tayl0rh
 */

#ifndef _PS_H_
#define _PS_H_

#include <stdlib.h>
#include "../DSP_Config.h"
#include "stereoSample.h"

void pitchShift(stereoSample* CodecDataIn, stereoSample* CodecDataOut);

#endif /* _PS_H_ */
