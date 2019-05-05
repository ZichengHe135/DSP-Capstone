#include "DSP_Config.h"
#include <stdio.h>
#include "fft.h"
#include "libmfcc.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

//#define PI 3.141592
#define BUFFERSIZE 256
int M=BUFFERSIZE;

int kk=0;
int startflag = 0;
int begining = 1;

volatile union {
	Uint16 sh;
	Uint8 i8[2];
} UARTout;


short X[BUFFERSIZE];
COMPLEX w[BUFFERSIZE];
COMPLEX B[BUFFERSIZE];
float feature;
float denominator = 0;
float numerator = 0;
float magnitude = 0;
float avg = 0;

int coeff=0;
double spectrum[BUFFERSIZE];
double mfcc_result[13]={0};
float llh;


volatile union {
	double sh;
	Uint8 i8[8];
} UARTdouble;

double wt[3][13]={{0.0122763877337223,
					0.351557346578024,
					-0.0964037640711843,
					-0.246449086817870,
					0.0458116923462825,
					-0.482892093610454,
					-0.0598701319872595,
					0.107602598464629,
					0.0224723391033042,
					-0.0436006338257361,
					0.200493742786855,
					-0.0147747075363160,
					0.195545685063345},
		          {-0.220419781336677,
		        	0.348810304385971,
					0.164677664671564,
					-0.548861496234596,
					-0.474772234599719,
					-0.666219330590195,
					-0.225447654706621,
					-0.529642012438904,
					-0.410866022375568,
					-0.541297864711420,
					0.298386255301210,
					0.0130867988089812,
					0.431632254353201},
		          {-0.186476539367078,
		        	-0.348765792618719,
					-0.191346800248933,
					0.0667037939968374,
					0.121419031765084,
					0.0626979713461138,
					0.172942803570683,
					0.0762544826697427,
					-0.163227917302585,
					0.0973962855074010,
					0.0259687176045914,
					0.130237638257834,
					-0.183006112290886}};


double beta[3]={-1.9242, 2.0448, 6.5058};
double tempgx[3] = {0,0,0};
double tempmax = 0;
int dd;
int label = -1;

int main()
{
  int N = 1;
  int D = 13;

  DSP_Init();

  Init_UART2(115200);

  //ReadParameters(params, 468); // receive SVM parameters from Matlab through UART

  int ii, mm, bb, ll;
  int cc = 0;
  int label = 0;

  for(ii=0; ii<M; ii++){
	  w[ii].real = cos((float)ii/(float)M*PI);
	  w[ii].imag = sin((float)ii/(float)M*PI);
  }

  // main stalls here, interrupts drive operation
  while(1) {
      if(startflag){
    	  // Remove bias (DC offset)
    	  avg = 0;
          for(mm=0; mm<M; mm++){
        	  avg = avg + X[mm];
          }
          // Measure the Magnitude of the input to find starting point
          avg = avg/M;
    	  magnitude = 0;
          for(mm=0; mm<M; mm++){
        	  magnitude = magnitude + abs(X[mm]-avg);
          }
          if(magnitude>30000){
        	  // N-blocks
        	  for(bb=0;bb<N;bb++){
        		  for(ll=0; ll<M; ll++){
        			  B[ll].real = X[10*bb+ll];
        			  B[ll].imag = 0;
        		  }
				  fft(B, M, w);

				  // Features for SVM : MFCC
				  for(mm=0; mm<M; mm++)
					   spectrum[mm] = sqrt(B[mm].real*B[mm].real + B[mm].imag*B[mm].imag);
				  for(coeff = 0; coeff < D; coeff++){
				  	  mfcc_result[coeff] = GetCoefficient(spectrum, 12000, 48, M, coeff);
				  }
        	  }
        	  	label = -1;
        	  	tempmax = 0;
				for(cc=0;cc<3;cc++){
					tempgx[cc]= 0;
					for(dd=0;dd<D;dd++){
						tempgx[cc] = tempgx[cc] + mfcc_result[dd]*wt[cc][dd];
					}
					tempgx[cc] = tempgx[cc] + beta[cc];
					if(tempmax<tempgx[cc]){
						label = cc;
						tempmax = tempgx[cc];
					}
				}
				printf("label: %d, gxDuck: %lf, gxDove: %lf, gxblueJay: %lf \n",label+1, tempgx[0], tempgx[1], tempgx[2]);
          }
        startflag = 0;
      }
  }
}
