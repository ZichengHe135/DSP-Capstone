/*
 * synth.cpp
 *
 *  Created on: May 23, 2019
 *      Author: taylor
 */

//C++-source: sys_unicode_for_c.hpp
#include "synth.hpp"
#include "library/rch_oscillators.h"
#include <math.h>


RCH::Oscillators::Triangle ch1;
RCH::Oscillators::Triangle ch2;
RCH::Oscillators::Triangle ch3;
RCH::Oscillators::Triangle ch4;
RCH::Oscillators::Saw ch5;
RCH::Oscillators::Saw ch6;
RCH::Oscillators::Saw ch7;
RCH::Oscillators::Saw ch8;



extern "C" void SYNTH_Init(){
    //std::cout << "not";
    ch1.setup(32000.0,120.0,0.25);
//    oscTriangle1.setup(32000.0,120.0*1.26,0.25);
//    oscTriangle2.setup(32000.0,120.0*1.5,0.25);
//    oscTriangle3.setup(32000.0,120.0*1.76,0.25);
    printf("working\n");
}

double mtof (Uint8 note) {
    return 440.0 * pow(2, (note-69.0)/12.0);  // totally working
}

extern "C" void SYNTH_UpdateSettings(){
    //std::cout << "not";
    if (IsDataReady_UART2()) {
        Uint8 uint = Read_UART2();
    //for(long i = 0; i < 1000000; i++);
      //  printf ("%f",  pow(2.0,4.0));
        ch1.setup(32000.0,mtof(uint),0.25);
    }
//for(;;);
//    oscTriangle1.setup(32000.0,120.0*1.26,0.25);
//    oscTriangle2.setup(32000.0,120.0*1.5,0.25);
//    oscTriangle3.setup(32000.0,120.0*1.76,0.25);
}

extern "C" short SYNTH_Tick(){
    //float** a = new float*[2];
    //for(int i = 0; i < 2; ++i)
    //    a[i] = new float[1];
    //float** tst  = buffer;
    return (short) (ch1.tick()
            //+oscTriangle1.tick()+oscTriangle2.tick()+oscTriangle3.tick())
            * (1<<12));
   // oscTriangle.fill(a,2,1);
}

