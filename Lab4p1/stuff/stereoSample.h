/*
 * stereoSample.h
 *
 *  Created on: May 8, 2019
 *      Author: tayl0rh
 */

#ifndef STUFF_STEREOSAMPLE_H_
#define STUFF_STEREOSAMPLE_H_

#include "../tistdtypes.h"

typedef volatile union {
	Uint32 ABC;
	Int16 Channel[2];
} stereoSample;

#endif /* STUFF_STEREOSAMPLE_H_ */
