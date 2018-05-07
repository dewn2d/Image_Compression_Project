/*
 ============================================================================
 Name        : Image_Compression_Project.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "Includes/encoder.h"
#include "Includes/decoder.h" 

void view_image(char* file);

int main(void) 
{
	
	encoder("Images/lena.raw");
	view_image("Images/lena.raw");

	return 0;
}

void view_image(char* file)
{
  	IplImage* img = 0; 
  	int height,width,step,channels;
  	uchar *data;
  	int i,j,k;

  	// load an image  
  	img=cvLoadImage(file,CV_LOAD_IMAGE_ANYCOLOR );

  	if(!img){
    		printf("Could not load image file: %s\n",file);
    		exit(0);
  	}
 
  	// get the image data
  	height    = img->height;
  	width     = img->width;
  	step      = img->widthStep;
  	channels  = img->nChannels;
  	data      = (uchar *)img->imageData;
  	printf("Processing a %dx%d image with %d channels\n",height,width,channels); 
 	
 	// create a window
 	cvNamedWindow("mainWin", CV_WINDOW_AUTOSIZE); 
 	cvMoveWindow("mainWin", 100, 100);
  	// show the image
  	cvShowImage("mainWin", img );
  	// wait for a key
  	cvWaitKey(0);
 	
  	// release the image
  	cvReleaseImage(&img );
  	
}


