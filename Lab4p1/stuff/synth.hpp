/*
 * synth.h
 *
 *  Created on: May 23, 2019
 *      Author: taylor
 */

#ifndef STUFF_SYNTH_HPP_
#define STUFF_SYNTH_HPP_


#include <stdio.h>
//#include <libtst.h>

//C/C++ - header "sys_unicode_for_c.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "../LCDK_Support_DSP.h"
//RCH::Oscillators::Triangle oscTriangle;

  void SYNTH_Init();
  short SYNTH_Tick();
  void SYNTH_UpdateSettings();
  void SYNTH_StartRecording(short recInput);

#ifdef __cplusplus
} //end extern "C"
#endif

#endif /* STUFF_SYNTH_HPP_ */
