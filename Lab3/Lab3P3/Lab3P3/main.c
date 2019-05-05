#include "DSP_Config.h"
#include <stdio.h>
#include "fft.h"
#include "gmm.h"
#include "libmfcc.h"
#include <math.h>
//#define PI 3.141592
#define BUFFERSIZE 256
int M=BUFFERSIZE;

int kk=0;
int startflag = 0;
int training = 1;
short X[BUFFERSIZE];
COMPLEX w[BUFFERSIZE];
COMPLEX B[BUFFERSIZE];
double Bmag[BUFFERSIZE];
float feature;
float denominator = 0;
float numerator = 0;
float magnitude = 0;
float avg = 0;
int coeff=0; double spectrum[BUFFERSIZE];
double mfcc_result[13]={0};
float llh;
GMM gmm[1]; // create GMM model

double weights[3] = {0.5477,0.2264,0.2259};

double means[39] = {22.1976687527070,3.81945412373297,1.26570613441347,-0.985661966002968,1.13295487106046,-0.549308176183768,0.640540649672768,-0.342443993345457,0.658952117360979,0.0774927068996723,0.367073039851897,-0.0748059954710994,0.435646305995509,
					27.5663493215067,7.35151872605306,3.29925739780430,-1.73459256744440,0.437121232555333,-2.67736735166019,-0.132841553407479,-1.88843845222991,-0.398990143985416,-1.39657833840316,0.337660059012280,-0.648269404980016,0.691696453628963,
					22.5553124702542,-4.88169881826363,-2.80455323884001,0.745136042961463,1.01908232767072,-1.25765811382354,1.06926283493756,0.875628021891903,-1.48088299332618,1.36249738161711,-1.18408254293371,1.74204158902496,-0.692658422907270};
double covars[39] = {274.9073,    6.3249,    1.8425,    1.3317,    1.8762,    0.8612,    0.5094,    0.4954,    0.3817,    0.1747, 0.3303,    0.1447,    0.2047,
		25.8485,    2.5260,    0.7377,    0.6041,    0.6041,    0.4006,    0.3469,    0.1172,    0.1252,    0.1252, 0.2656,    0.1628,    0.1476,
		272.4916,    2.5234,    0.8289,    0.4925,    0.7460,    0.7126,    0.2626,    0.5398,    0.1998,    0.5167, 1.0166,    0.4696,    1.0181};

int main()
{
	int K = 3; // Number of Classes
	int N = 1; // Number of Blocks
	int D = 13; // Number of Features
	DSP_Init();
	int ii, mm, bb, ll, i;

	// Initialize GMM model
	gmm_new(gmm, K, D, N, "diagonal");
	gmm_set_convergence_tol(gmm, 1e-6);
	gmm_set_regularization_value(gmm, 1e-6);
	gmm_set_initialization_method(gmm, "random");
	// (P3). Update GMM parameters (gmm[0]) through UART communication with Matlab
	gmm->means = means;
	gmm->covars = covars;
	gmm->weights = weights;
//	  for (i=0; i<39; i++) {
//		  gmm->means[i] = mu[i];
//		  gmm->covars[i] = sigma[i];
//	  }
//	  for (i=0; i<3; i++) {
//		  gmm->weights[i] = weight[i];
//	  }

	// Twiddle factor
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
						B[ll].real = X[ll];
						B[ll].imag = 0;
					}
					fft(B,M,w);
					for (i = 0; i < M; i++) {
						Bmag[i] = sqrt(B[i].real * B[i].real + B[i].imag * B[i].imag);

					}
					// (P3). FFT: B is input and output, w is twiddle factors

					for (i = 0; i < D; i++) {
						mfcc_result[i]=GetCoefficient(Bmag,12E3,48, M, i);
					}
					// (P3). Find 13 MFCC coefficients
				}
				// (P3). Print GMM score using gmm model and mfcc_result

				llh = gmm_score(gmm, mfcc_result, N);
				//printf("llh=%f\n", llh);
			}
			startflag = 0;
		}
	}
}
