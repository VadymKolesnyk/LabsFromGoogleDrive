//Автор - Коленик Вадим
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <windows.h>

int main()
{
	double eps[2] = { 0.01,0.0001 }, s = 1.0, a = 1.0, x = 0.0, z=0.0;
	int n = 0,i = 0;
	SetConsoleOutputCP(1251);
	printf("Введите x є (-1;1):\nx=");
	scanf("%lf", &x);
	if (fabs(x) < 1) {
		z = 1.0 / (1 + x * x);
		for (i = 0; i < 2; i++) {
			printf("eps=\t\t%1.15f\n1/(1+x^2)=\t%1.15f\n", eps[i], z);
			s = 1.0;
			while (fabs(a) > eps[i]) {
				a = -a * x * x;
				s = s + a;
				n++;
			}
			printf("s=\t\t%1.15f\nn=\t\t%i\n\n", s, n);
			a = 1.0;
			n = 0;
		}
	}else printf("Неверное значение x\n");
	system("pause");
	return 0;
}