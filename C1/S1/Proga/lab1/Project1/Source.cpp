//Автор - Коленик Вадим
#include <stdio.h>
#include <math.h>

int main()
{
	float x, y, a = 4.5e-4, b = -2e-5;
	int c = 25;
	x = pow(1 + tan(a / 2)*tan(a / 2), sqrt(fabs(b) + c));
	y = 2 / tan(a / fabs(b));
	printf("x=%1.15f\ny=%1.15f\n", x, y);
	getchar();
	return 0;
} 
