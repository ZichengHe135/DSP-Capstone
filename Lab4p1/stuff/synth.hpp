/*
 * synth.h
 *
 *  Created on: May 23, 2019
 *      Author: taylor
 */

#ifndef STUFF_SYNTH_HPP_
#define STUFF_SYNTH_HPP_

//C/C++ - header "sys_unicode_for_c.h"

#ifdef __cplusplus
extern "C" {
#endif

//RCH::Oscillators::Triangle oscTriangle;

  void SYNTH_Init();
  short SYNTH_Tick();

#ifdef __cplusplus
} //end extern "C"
#endif

#endif /* STUFF_SYNTH_HPP_ */
