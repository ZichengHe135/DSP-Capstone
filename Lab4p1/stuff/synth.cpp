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
#include <algorithm>
#define clamp(x,y,z) std::max(y, std::min(x,z))
#include <stdio.h>

RCH::Oscillators::Sine ch1;
RCH::Oscillators::Triangle ch2;
RCH::Oscillators::Triangle ch3;
RCH::Oscillators::Triangle ch4;
RCH::Oscillators::Saw ch5;
RCH::Oscillators::Saw ch6;
RCH::Oscillators::Saw ch7;
RCH::Oscillators::Saw ch8;



extern "C" void SYNTH_Init(){
    //std::cout << "not";
    ch1.setup(8000.0,50.0,0.0);
//    oscTriangle1.setup(32000.0,120.0*1.26,0.25);
//    oscTriangle2.setup(32000.0,120.0*1.5,0.25);
//    oscTriangle3.setup(32000.0,120.0*1.76,0.25);
    printf("working\n");
}

double mtof (Uint8 note) {
    return 440.0 * pow(2, (note-69.0)/12.0);  // totally working
}
unsigned char uart = 0;
extern "C" char echoEnable;
extern "C" void SYNTH_UpdateSettings(){
    //std::cout << "not";

    if (IsDataReady_UART2()) {
        unsigned char uart2 = Read_UART2();
        if (uart2 == uart) {

        }
        else if (uart2 != 0) {  // actually do sh!t
            //printf ("%x\n", uart2);
            //fflush(stdin);
            if(uart2 & 0x80) {
                // set the effects mode
                switch (uart2) {
                    case 0x80:
                        echoEnable = !echoEnable;
                       break;
                    case 0x81:
                        //echoEnable = 0;
                        break;




                }
            } else {
            ch1.setup(32000.0,mtof(uart2),0.25);
            }
        }
        uart = uart2;


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
    return (short) (clamp(ch1.tick()
            //+oscTriangle1.tick()+oscTriangle2.tick()+oscTriangle3.tick())
            ,-1.0,0.999999999999)* (1<<15));
   // oscTriangle.fill(a,2,1);
}

