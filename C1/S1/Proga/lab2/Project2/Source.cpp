//Автор - Коленик Вадим
#include <stdio.h>
#include <math.h>

int main()
{
	float y = 0, a = 0.7, dx = 0.5, x = -2;
	while (x < 0)
	{
		y = 2 * a*log(-x);
		printf("If x=%4.1f,\t y=%18.15f\n", x, y);
		x = x + dx;
	}
	y = 0.0;
	printf("If x=%4.1f,\t y=%18.15f\n",x,y);
	x = dx;
	while (x <= 3)
	{
		y = sqrt((x*x*x) / (x + a)) - log(x);
		printf("If x=%4.1f,\t y=%18.15f\n", x, y);
		x = x + dx;
	}
	getchar();
	return 0;
}