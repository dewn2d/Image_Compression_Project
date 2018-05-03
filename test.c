#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 8
#define N 8


float* zzscan(float input[][N]);

int main(void)
{

	int i,j;
	float* mat2;
	float mat[M][N] = {{   1,   5,  54, 255, 255,   8, 255,   4 },
            		   {  75,   8,  32, 255,   5,  65,  29, 255 },
            		   {  65,  45, 255, 255, 255,   7, 255,   0 },
            		   { 255,  23,   1, 255,  54, 255, 255, 255 },
            		   { 255,  34, 255,   4, 255,   6, 255, 255 },
            		   {   0,   6, 255,  75,   7,  86, 255, 255 },
            		   { 255, 255,  73,  84, 255, 255, 255, 255 },
            		   {   0, 255,  28, 255,   0, 255, 255, 255 } };


	for(i=0;i<M;i++){
		for(j=0;j<N;j++)
			printf("%.0f ",mat[i][j]);
		printf("\n");
	}
	printf("\n");
	
	mat2 = zzscan(mat);

	for(i=0;i<N*M;i++)
		printf("%.0f\n",mat2[i]);

	return 0;

}

float* zzscan(float input[][N])
{

	int n = N*M;
 	float *scanArray = (float *) malloc(n * sizeof(float)); 
	memset(scanArray,0,sizeof(scanArray));
	int i=0, j=0, k=0;
	int count = 0;


	while(k<n)
	{
		if(k == 0){
			scanArray[k] = input[i][j];
			k++;
		}
		
		else if(i == N-1)
		{
			j++;
			while (j<=N-1)
			{
				scanArray[k] = input[i][j];
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
				scanArray[k] = input[i][j];	
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
				scanArray[k] = input[i][j];	
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
				scanArray[k] = input[i][j];
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
