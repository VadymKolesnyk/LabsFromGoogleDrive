//Автор - Коленик Вадим
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <Windows.h>

void main()
{
	SetConsoleOutputCP(1251);
	unsigned n, min_i, i;
	float x, min, k, l;
	printf("Введите натуральное n=");
	scanf_s("%u", &n);
	printf("Введите действительное х=");
	scanf_s("%f", &x);
	printf("----------------------------------\n");
	printf("S(k)  = exp(cos(x^(2*k)))*sin(x^(3*k))\n\n");
	min = exp(cos(x*x))*sin(x*x*x);
	min = fabs(min - round(min));
	min_i = 1;
	for (i = 1; i <= n; i++)
	{
		k = exp(cos(pow(x, 2 * i)))*sin(pow(x, 3 * i));
		l = fabs(k - round(k));
		printf("S(%2d) = %18.15f\t%f\n", i, k, l);
		
		if (l < min)
		{
			min_i = i;
			min = l;
		}
	}
	k = exp(cos(pow(x, 2 * min_i)))*sin(pow(x, 3 * min_i));
	printf("----------------------------------\n");
	printf("Ближайшее к какому-нибудь целому: S(%d) = %0.15f\n\n\n", min_i, k);
	system("pause");
}