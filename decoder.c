#include "Includes/decoder.h"

void decoder( char* image_file)
{
	
	int i, j, k;
	int rows = 512;
	int cols = 512;

	unsigned char buff[rows*cols];
	unsigned char image[rows][cols];

	FILE* datafp;
	FILE* imagefp;

	datafp = fopen("arithoutput.txt", "r");
	imagefp = fopen("Images/output.512", "w");

	for( i =0; i<rows; i++)
	{
		for( j =0; j<cols; j++)
		{
			
			fscanf(datafp, "%s ", &image[j][i]);
		}
	}

	fclose(datafp);

	float intemp[M][N] = {{0}};
	float iqtemp[M][N] = {{0}};
	float outtemp[M][N] = {{0}};

	int shift_rt = 0;
	int shift_dn = 0;

	for( i=0; i<((rows*cols)/D); i++)
	{	

		memset(intemp,0,sizeof(intemp));
		memset(iqtemp,0,sizeof(intemp));
		memset(outtemp,0,sizeof(intemp));

		for( j=0; j<M; j++)
		{
			for( k=0; k<N; k++)
			{
				intemp[j][k] = image[(shift_dn*M)+j][(shift_rt*N)+k];
			}	
		}
		
		Iquantize(intemp, iqtemp);
		IDCT(iqtemp, outtemp);

		for( j=0; j<M; j++)
		{
			for( k=0; k<N; k++)
			{
				image[(shift_dn*M)+j][(shift_rt*N)+k] = outtemp[j][k];
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

	for(int i =0; i < rows; i++)
	{
		for(int j = 0; j < cols;j++)
		{
			buff[(i*cols)+j] = image[j][i]; 
 		}
	}

	size_t n = fwrite( buff, sizeof(buff[0]), sizeof(buff), imagefp );

	fclose( imagefp);
}



void Iquantize( float input[][N], float output[][N])
{
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
