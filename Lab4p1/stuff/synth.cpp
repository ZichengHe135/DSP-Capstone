/*
 * synth.cpp
 *
 *  Created on: May 23, 2019
 *      Author: taylor
 */

//C++-source: sys_unicode_for_c.hpp
#include "library/rch_oscillators.h"
#include <stdio.h>
//#include <libtst.h>



RCH::Oscillators::Triangle oscTriangle;
RCH::Oscillators::Triangle oscTriangle1;
RCH::Oscillators::Triangle oscTriangle2;
RCH::Oscillators::Triangle oscTriangle3;



extern "C" void SYNTH_Init(){
    printf("working\n");
    //std::cout << "not";
    oscTriangle.setup(32000.0,120.0,0.25);
    oscTriangle1.setup(32000.0,120.0*1.26,0.25);
    oscTriangle2.setup(32000.0,120.0*1.5,0.25);
    oscTriangle3.setup(32000.0,120.0*1.76,0.25);
}

extern "C" short SYNTH_Tick(){
    //float** a = new float*[2];
    //for(int i = 0; i < 2; ++i)
    //    a[i] = new float[1];
    //float** tst  = buffer;
    return (short) ((oscTriangle.tick()+oscTriangle1.tick()+oscTriangle2.tick()+oscTriangle3.tick()) * (1<<12));
   // oscTriangle.fill(a,2,1);
}

