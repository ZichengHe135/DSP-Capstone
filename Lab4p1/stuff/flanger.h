// Author:  Zicheng He
// Date:    May 29th 2019
// File:    flanger.h
//

#ifndef _FLANGER_H_
#define _FLANGER_H_

#include <stdlib.h>
#include "../DSP_Config.h"
#include "stereoSample.h"

void flanger(stereoSample* CodecDataIn, stereoSample* CodecDataOut, short* fla_bufL, short* fla_bufR);

#endif /* _FLANGER_H_ */
