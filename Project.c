/*
 ============================================================================
 Name        : Image_Compression_Project.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "encoder.h"
#include "decoder.h"

int main(void) 
{
	int i,j,k,cols,rows;
	
	struct DCcoeff DC ={
		.size = 0,	
	};

	rows = cols = 512;

	unsigned char buff[rows*cols];
	unsigned char image[rows][cols];

	FILE* imagefp;
	FILE* fp;

	imagefp = fopen("lena.512", "r");
	//fp = fopen("mat.txt", "w");

	size_t n = fread( buff, sizeof(buff[0]), sizeof(buff), imagefp );
	fclose(imagefp);
	for(int i =0; i < rows; i++)
	{
		for(int j = 0; j < cols;j++)
		{
			image[j][i] = buff[(i*cols)+j];
 		}
	}
	
	float image_mats[D*D][M][N]= {{{0}}};

	int shift_rt = 0;
	int shift_dn = 0;
	for( i=0; i<((rows*cols)/D); i++)
	{	
		
		for( j=0; j<M; j++)
		{
			for( k=0; k<N; k++)
			{
				image_mats[i][j][k] = image[(shift_dn*M)+j][(shift_rt*N)+k];
			}	
		}
		/*
		if (shift_rt==0){
			printf("%d\n",i);
			print_mat(image_mats[i]);
		}
		*/
		if(shift_rt < M*N-1)
			shift_rt++;
		
		else
		{
			shift_dn++;
			shift_rt=0;
		}
	}

	/*
	for (i = 0; i < rows; ++i) {
		for( j =0; j<cols; j++)
			fprintf(fp,"%d ", image[i][j]);
		fprintf(fp,"\n");
	}
	fclose(fp);*/

	float dct[D*D][M][N] = {{{0}}};
	float idct[D*D][M][N] = {{{0}}};
	float quant[D*D][M][N] = {{{0}}};
	float* zscanmat; 
	float ampsizemat[D*D][M*N][3] = {{0}}; 

	// *************encoding***************
	for( i=0; i<((rows*cols)/D); i++)
	{	
		
		DCT(image_mats[i], dct[i]);
		uni_quantizer(dct[i],quant[i],9);
		zscanmat = zzscan(quant[i]);
		DC = ampsize( zscanmat, ampsizemat[i], DC );

		if(i == ((rows*cols)/D) - 1){
			print_mat(image_mats[i]);
			print_mat(dct[i]);
			print_mat(quant[i]);

			for(j=0;j<N*M;j++)
				printf("%.0f ",zscanmat[j]);
			printf("\n\n");
	
			DC = ampsize( zscanmat, ampsizemat[i], DC );
	
			
			for( j=0; j<D; j++)
				printf("(%.0f,%.0f)(%.0f), ",ampsizemat[i][j][0],ampsizemat[i][j][1],ampsizemat[i][j][2]);
			printf("\n");	
		
		}
		free(zscanmat);	
	}
	/*
	for( i=0; i<DC.size; i++)
	{	
		printf("%.0f ", DC.coeff[i]);
		if(i%rows == 0)
			printf("\n\n");
	}
	printf("%d\n",DC.size);
	*/
	
	/*DCT(mat, dct);
	uni_quantizer(dct,quant,9);
	zscanmat = zzscan(quant);

	print_mat(mat);
	print_mat(dct);
	print_mat(quant);

	for(i=0;i<N*M;i++)
		printf("%.0f ",zscanmat[i]);
	printf("\n\n");
	
	DC = ampsize( zscanmat, ampsizemat, DC );
	*/
	

	//*************decoding**************** 
	//IDCT(dct,idct);
	//print_mat(idct);
	
	return 0;
}



