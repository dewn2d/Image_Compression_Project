#ifndef DECODER_H_   
#define DECODER_H_

#include "inc_def.h"

void Iquantize( float input[][N], float output[][N]);
void IDCT(float input[][N], float output[][N]);
float alpha(int input);

#endif 
