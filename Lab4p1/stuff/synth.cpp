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
RCH::Oscillators::Saw ch3;
RCH::Oscillators::Square ch4;
RCH::Oscillators::Pulse ch5;
RCH::Oscillators::SquarePulse ch6;
RCH::Oscillators::Sampler ch7;
//RCH::Oscillators::Saw ch8;

#define SAMPLERBUF 0x100000

unsigned char uart = 0; // prev. uart d flipflop not
unsigned char channel = 0;

// VirtualSWitches
extern "C" char echoEnable;
extern "C" char reverbEnable;
extern "C" char flangerEnable;
extern "C" char vibEnable;
extern "C" char psEnableHiLow;

extern "C" char thru;
char thru = 0;

// sampler pt 2
extern "C" char startRecording;
char startRecording = 0;
unsigned long isrI = 0;
unsigned long sampleSize=SAMPLERBUF;
#pragma DATA_SECTION ("CE0");
short sample[SAMPLERBUF];

extern "C" void SYNTH_StartRecording(short recInput) {
    if (startRecording == 1) {
        startRecording++;
        isrI = 0;
    }
    sample[isrI++] = recInput;
    if(isrI >= SAMPLERBUF) {
        startRecording = 0;
    }
    sampleSize = SAMPLERBUF;
    ch7.settheBuffer(sample, sampleSize);
}

extern "C" void SYNTH_Init(){
    //std::cout << "not";
    ch1.setup(32000.0,120.0,0.2f);
    //ch3.setup(32000.0,120.0*1.0,0.1f);
    //ch6.setup(32000.0,120.0*1.0,0.0F);
    ch5.setPulseWidth(0.5);
    ch6.setWidth(0.5);
    //ch7.setup(0.0,120.0*1.0,0.0F);
    ch7.settheBuffer(sample, sampleSize);
    printf("working\n");
}

double mtof (Uint8 note) {
    return 440.0 * pow(2, (note-69.0)/12.0);  // totally working
}



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
                        reverbEnable = !reverbEnable;
                        break;
                    case 0x82:
                        vibEnable = !vibEnable;
                       break;
                    case 0x83:
                       flangerEnable = !flangerEnable;
                       break;

                    case 0x84:
                        psEnableHiLow ^= 1;
                        break;
                    case 0x85:
                        psEnableHiLow ^= 2;
                        break;

                    case 0x90 ... 0x9F: // switch instrument
                        channel = uart2 - 0x90;
                        break;
                    case 0xA0 ... 0xAF: // various duty cycle change
                        ch5.setPulseWidth(((double)uart2-0x9f)/16.0);
                        ch6.setWidth(((double)uart2-0x9f)/16.0);
                        break;
                    case 0xB0: // sampler rec.
                        if(startRecording) {
                            sampleSize = isrI;
                            ch7.settheBuffer(sample, sampleSize);
                        }

                        startRecording = !startRecording;
                        break;
                    case 0xB1: // line-in play-through.
                        thru != thru;
                        break;

                    case 0xff:
                    ch1.noteOff();
                    ch2.noteOff();
                    ch3.noteOff();
                    ch4.noteOff();
                    ch5.noteOff();
                    ch6.noteOff();
                    ch7.noteOff();
                    break;


                }
            } else {
                switch (channel){
                    case 0:
                        ch1.setup(32000.0,mtof(uart2),0.3f);
                        break;
                    case 1:
                        ch2.setup(32000.0,mtof(uart2),0.3f);
                        break;
                    case 2:
                        ch3.setup(32000.0,mtof(uart2),0.15f);
                        break;
                    case 3:
                        ch4.setup(32000.0,mtof(uart2),0.15f);
                        break;
                    case 4:
                        ch5.setup(32000.0,mtof(uart2),0.15f);
                        break;
                    case 5:
                        ch6.setup(32000.0,mtof(uart2),0.15f);
                        break;
                    case 6:
                        ch7.setup(440.0,mtof(uart2),1.0f);
                        break;
                }

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
            +ch5.tick()+ch6.tick()+ch2.tick()+ch3.tick()+ch4.tick() + ch7.tick()
            ,-1.0,0.999999999999)* (1<<15));
   // oscTriangle.fill(a,2,1);
}

