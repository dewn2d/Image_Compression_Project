#include "decoder.h"

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
