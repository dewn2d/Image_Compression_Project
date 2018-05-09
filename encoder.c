#include "Includes/encoder.h"

int coeff[9][3] = { 
	{ 2,  2,   3},
	{ 3,  4,   7},
	{ 4,  8,  15},
	{ 5, 16,  31},
	{ 6, 32,  63},
	{ 7, 64, 127},
	{ 8,128, 255},
	{ 9,256, 511},
	{10,512,1023}};

int encoder(char* image_file)
{
	
	int i,j,k;
	
	struct DCcoeff DC ={
		.size = 0,	
	};
	
	// size of image
	int rows = 512;
	int cols = 512;

	unsigned char buff[rows*cols];
	unsigned char image[rows][cols];

	FILE* imagefp;
	FILE* DCTStream;

	imagefp = fopen( image_file, "r"); //open input image
	DCTStream = fopen( "Outputs/DCTStream.txt", "w"); // open file to store DCT coefficents DC and AC
	//fp = fopen("Outputs/mat.txt", "w");
	
	size_t n = fread( buff, sizeof(buff[0]), sizeof(buff), imagefp ); // read pixel data from imate
	fclose(imagefp);
	for( i =0; i < rows; i++)
	{
		for( j = 0; j < cols;j++)
		{
			image[j][i] = buff[(i*cols)+j]; // form a matrix of the input values
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
				image_mats[i][j][k] = image[(shift_dn*M)+j][(shift_rt*N)+k]; // divide the matrix into 64 8*8 matrices for DCT transform
			}	
		}
		/*
		if (shift_rt==0){
			printf("%d\n",i);
			print_mat(image_mats[i]);
		}
		*/
		if(shift_rt < M*N-1)
			shift_rt++; //move right till you reach the 63 which will be the last 8*8 matrix in the row
		
		else
		{
			shift_dn++; // if you reach the last matrix in row got to next row
			shift_rt=0; // start at beginning
		}
	}
	

	/*************encoding***************/
	float dct[D*D][M][N] = {{{0}}};
	float idct[D*D][M][N] = {{{0}}};
	float quant[D*D][M][N] = {{{0}}};
	float ampsizemat[D*D][M*N][3] = {{0}}; 

	for( i=0; i<((rows*cols)/D); i++)
	{	
		
		DCT(image_mats[i], dct[i]); //compute dct transform of matrix
		uni_quantizer(dct[i],quant[i],9); //quantize matrix
		float* zscanmat = zzscan(quant[i]); // zigzag scan matrix
		DC = ampsize( zscanmat, ampsizemat[i], DC ); //get Size + amplitude representation of coefficients
	
		for(j=0;j<N*M;j++)
			fprintf(DCTStream, "%.0f ",zscanmat[j]); //save strema of DCT coefficents into file for the arithmatic coder
		
		if(i < 1){ //printing for debugging
			print_mat(image_mats[i]);
			print_mat(dct[i]);
			print_mat(quant[i]);
		
			for(j=0;j<N*M;j++)
				printf("%.0f ",zscanmat[j]);
			printf("\n\n");
	
			/*
			for( j=0; j<D; j++)
				printf("(%.0f,%.0f)(%.0f), ",ampsizemat[i][j][0],ampsizemat[i][j][1],ampsizemat[i][j][2]);
			printf("\n");	
			*/
		}
		free(zscanmat);	
	}
	//printf("hellow\n");
	/*for( i=0; i<DC.size; i++)
	{	
		fprintf(DCTStream, "%.0f ", DC.coeff[i]);
		//printf("%d\n",i);
	}*/

	//printf("%d\n",DC.size);

	fclose(DCTStream);
	
	return 0;

}

void uni_quantizer(float input[][N], float output[][N], float stp_size)
{

	int i,j,k;

	for ( i=0; i<M; i++)
	{
		for ( j=0; j<M; j++)
		{
			
			output[i][j] = round(input[i][j]/stp_size);
			if(output[i][j] == -0.0)
				output[i][j] = 0.0;
		}
	}

}

float* zzscan(float input[][N])
{

 	float *scanArray = (float *) malloc(D * sizeof(float)); 
	memset(scanArray,0,sizeof(scanArray));
	int i=0, j=0, k=0;
	int count = 0;

	while(k<D)
	{
		if(k == 0){
			scanArray[k] = input[j][i];
			k++;
		}
		
		else if(i == N-1)
		{
			j++;
			while (j<=N-1)
			{
				scanArray[k] = input[j][i];
				//printf("a\t%d\t%d\t%d\t%.0f\n",k,i,j,scanArray[k]);
				k++;
				if(j!=N-1){
					i--;
					j++;
				}
				else break;	
			}
			//printf("k%d\ti%d\tj%d\n\n",k,i,j);

		}

		else if(j == N-1 )
		{	
			i++;
			while (i<=N-1)
			{	
				scanArray[k] = input[j][i];	
				//printf("b\t%d\t%d\t%d\t%.0f\n",k,i,j,scanArray[k]);
				k++;
				if(i!=N-1){
					i++;
					j--;
				}
				else break;
			}
			//printf("k%d\ti%d\tj%d\n\n",k,i,j);
		}

		else if(j == 0)
		{	
			i++;
			count++;
			while (i>=0)
			{	
				scanArray[k] = input[j][i];	
				//printf("c\t%d\t%d\t%d\t%.0f\n",k,i,j,scanArray[k]);
				k++;
				if(i!=0){
					i--;
					j++;
				}
				else break;
			}
			//printf("k%d\ti%d\tj%d\n\n",k,i,j);
		}
		
		else if(i == 0)
		{
			j++;
			while (j>=0)
			{
				scanArray[k] = input[j][i];
				//printf("d\t%d\t%d\t%d\t%.0f\n",k,i,j,scanArray[k]);
				k++;
				if(j!=0){
					i++;
					j--;
				}
				else break;	
			}
			//printf("k%d\ti%d\tj%d\n\n",k,i,j);

		}
	}

	return scanArray;
}

float* rasterscan(float input[][N])
{

	float *scanArray = (float *) malloc(D * sizeof(float)); 
	memset(scanArray,0,sizeof(scanArray));
	int i=0, j=0, k=0;
	int count = 0;

	while(k<D)
	{
		
		if(j%2 ==0)
		{
			for(i =0; i<M; i++)
			{
			
				scanArray[k] = input[i][j];
				k++;
			}
		}
		
		else if(j%2 ==1)
		{
			for(i =M; i>0; i--)
			{
				
				scanArray[k] = input[i][j];
				k++;
			}
		}

		j++;
		
	}

	return scanArray;

}

struct DCcoeff ampsize(float* input, float array[][3], struct DCcoeff DC)
{
	
	int i,j;
	int lead0=0;

	for(i=0; i< D; i++)
	{
		if( i == 0)
		{
			array[i][0] = 0;
			if(DC.size == 0)
				array[i][2] = input[i];
			else
				array[i][2] = input[i] - DC.coeff[DC.size-1];

			DC.coeff[DC.size] = input[i];
			DC.size++;

			for ( j=0; j<9; j++)
			{		
				if((input[i] >= coeff[j][1] && input[i] <= coeff[j][2]) ||
					(input[i] >= -coeff[j][2] && input[i] <= -coeff[j][1]))
				{
					array[i][1] = coeff[j][0];
				}
			}
			
		}

		else
		{
			if(input[i] == 0)
				lead0++;

			else if(input[i] == 1 || input[i] == -1)
			{
				array[i][0] = lead0;
				array[i][1] = 1;
				array[i][2] = input[i];
				lead0 = 0;
			}
			
			else{		
	
				for ( j=0; j<9; j++)
				{		
					if((input[i] >= coeff[j][1] && input[i] <= coeff[j][2]) ||
						(input[i] >= -coeff[j][2] && input[i] <= -coeff[j][1]))
					{
						array[i][0] = lead0;
						array[i][1] = coeff[j][0];
						array[i][2] = input[i];
						lead0 = 0;	
					}
				}
			}
		}
	}

	return DC;

}

void DCT(float input[][N], float output[][N])
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
						cos( ((2*m + 1)*k*pi)/(16.0) )*
						cos( ((2*n + 1)*l*pi)/(16.0) );
					
				}
			}
			//printf("\n");
			output[k][l] =  lambda(k)*lambda(l)*(1.0/4.0)*temp;
			//printf("%f, %f, %f\n",sqrt(2/(float)N)*sqrt(2/(float)M),temp, output[k][l]);

		}
		//printf("\n");
	}
	//printf("%f\n",sqrt(2/(float)N)*sqrt(2/(float)M));
	
}

float lambda(int i)
{
	if( i == 0 )
		return 1.0/sqrt(2.0);
	else
		return 1.0;
}	

void get_bitrate( void )
{

	FILE* bitfp;
	char *bits = malloc(1000 * sizeof(char));
	bitfp = fopen( "map.art", "r" );
	int size;
	do
	{
		*bits++ = (char)fgetc(bitfp);
		size++;

	}while(*bits != EOF);
	
	
}

void print_mat(float input[][N])
{
	int i, j;
	for( i=0; i<8;i++){
		for(j =0; j<8; j++){
			printf("%.1f\t", input[i][j]);
		}
		printf("\n");
	}

	printf("\n");
}


