#ifndef DECODER_H_   
#define DECODER_H_

#include "inc_def.h"

int decoder( char* image_file);
void Iquantize( float input[][N], float step_size);
void IDCT(float input[][N], float output[][N]);
float alpha(int input);
float PSNR(void);

#endif 
