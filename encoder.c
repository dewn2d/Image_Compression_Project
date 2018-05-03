#include "encoder.h"

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
					temp +=input[m][n]*
						cos( ((2*m + 1)*k*pi)/(2*(float)M) )*
						cos( ((2*n + 1)*l*pi)/(2*(float)N) );
					
					//printf("%f\n",temp);
				}
			}
			//printf("\n");
			output[k][l] =  lambda(k)*lambda(l)*sqrt(2/(float)N)*sqrt(2/(float)M)*temp;
			//printf("%f, %f, %f\n",sqrt(2/(float)N)*sqrt(2/(float)M),temp, output[k][l]);

		}
		//printf("\n");
	}
	//printf("%f\n",sqrt(2/(float)N)*sqrt(2/(float)M));
	
}

float lambda(int i)
{
	if( i == 0 )
		return 1/sqrt(2);
	else
		return 1;
}	

void print_mat(float input[][N])
{
	for(int i=0; i<8;i++){
		for(int j =0; j<8; j++){
			printf("%.1f\t", input[i][j]);
		}
		printf("\n");
	}

	printf("\n");
}


