#ifndef ENCODER_H_   
#define ENCODER_H_

#include "inc_def.h"

struct DCcoeff{

	float coeff[D*D];
	float prev_co;
	int size;
	
};

float lambda(int i);
struct interval* lvl_gen( int numlvls, int a, int b );
void uni_quantizer(float input[][N], float output[][N], float stp_size);
float* zzscan(float input[][N]);
struct DCcoeff ampsize(float* input, float array[][3], struct DCcoeff DC);
void DCT(float input[][N], float output[][N]);
void print_mat(float input[][N]);

#endif 
