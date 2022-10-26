#include <stdio.h>
int main(void)
{
	float a = 2;
	const double h = 1e-3;
	double x = 0;
	printf("please enter the a \n");
	//scanf("%f", &a);
	float z = a;
	float y = a;
	printf("x     y \n");
	printf("%f     %f\n", x, y);
	x = x + h;
	y = (1-h/2) *y/ (1+h/2) ;
	printf("%f     %f\n", x, y);
	double k ;	
	k = z - y;
	while (k >= 0.001)
	{
		x = x + h;
		y = (1-h/2) / (1+h/2) * y;
		z = (1-h/2) / (1+h/2) * z;
		k = z - y;
		printf("%f     %f\n", x, y);
		
		
		}
	
	
	return 0;
	
}

