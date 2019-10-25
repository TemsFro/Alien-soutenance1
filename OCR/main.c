#include <stdio.h>
#include <err.h>
#include <math.h>
#include "xor.h"
int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		errx(1, "main: int1 int2");
	}
	int input1 = 0;
	int input2 = 0;
	if (argv[1][0]=='1')
		input1=1;
	if (argv[2][0]=='1')
		input2=1;
	double res = training(input1, input2);
	printf("résultat: %f\n", res);
	return 0;
}	
