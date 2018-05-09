#include "Includes/decoder.h"

int decoder( char* image_file)
{
	
	int i, j, k;
	int rows = 512;
	int cols = 512;

	unsigned char buff[rows*cols];
	unsigned char image[rows][cols];

	FILE* datafp;
	FILE* imagefp;

	datafp = fopen("arithoutput.txt", "r"); // open file of arithmatic decoded data
	imagefp = fopen("Images/output.512", "w");// open file for final image

	for( i =0; i<rows; i++)
	{
		for( j =0; j<cols; j++)
		{
			
			fscanf(datafp, "%s ", &image[j][i]); // creat matrix of decoded data
		}
	}

	fclose(datafp);

	/**************decoder***************/
	float intemp[M][N] = {{0}};
	float outtemp[M][N] = {{0}};

	int shift_rt = 0;
	int shift_dn = 0;

	for( i=0; i<((rows*cols)/D); i++)
	{	

		memset(intemp,0,sizeof(intemp));
		memset(outtemp,0,sizeof(intemp));

		for( j=0; j<M; j++)
		{
			for( k=0; k<N; k++)
			{
				intemp[j][k] = image[(shift_dn*M)+j][(shift_rt*N)+k]; // get a 8*8 matrix out of image matrix
			}	
		}
		
		Iquantize(intemp, 9); // inverse quantize matrix
		IDCT(intemp, outtemp); // inverse DCT trasnform matrix

		for( j=0; j<M; j++)
		{
			for( k=0; k<N; k++)
			{
				image[(shift_dn*M)+j][(shift_rt*N)+k] = outtemp[j][k]; // put matrix back into image matrix
			}	
		}

		if(shift_rt < M*N-1)
			shift_rt++;
		
		else
		{
			shift_dn++;
			shift_rt=0;
		}
	}

	for( i =0; i < rows; i++)
	{
		for(j = 0; j < cols;j++)
		{
			buff[(i*cols)+j] = image[j][i]; //load buffer writing to file
 		}
	}

	size_t n = fwrite( buff, sizeof(buff[0]), sizeof(buff), imagefp ); //write data to file

	fclose( imagefp);

	return 0;

}



void Iquantize( float input[][N], float step_size)
{

	int i, j;
	
	for( i=0; i<M; i++)
	{
		for( j=0; j<N; j++)
		{
		
			input[i][j] = input[i][j]*step_size;
		
		}
	}

}	

void IDCT(float input[][N], float output[][N])
{

	float temp;
	int m,n,l,k;

	for ( k=0; k<N; k++)
	{ 
		for ( l=0; l<N; l++)
		{
			temp = 0.0;
			for ( m=0; m<M; m++)
			{
				for (n =0; n<N; n++)
				{
					temp += input[m][n]*
						cos(((2*k + 1)*m*pi)/(2*M))*
						cos(((2*l + 1)*n*pi)/(2*N))*
						alpha(m)*alpha(n);
				}
			}
			output[k][l] = sqrt(2/(float)N)*sqrt(2/(float)M)*temp ; 
			//printf("%f, %f, %f\n",c(k)*c(l),temp, output[k][l]);

		}
	}

	
}

float alpha(int input)
{

	if (input == 0)
		return 1/sqrt(2.0);
	else 
		return 1;

}

float PSNR(void)
{
return 0.0;
}
