//Автор - Коленик Вадим
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <Windows.h>

int main() {
	SetConsoleOutputCP(1251);

	unsigned int n = 1, i = 0,  N = 1;
	printf("Введите n=");
	scanf("%u", &n);
	N = n * 2 ;
	printf("Введите постедовательность %u чисел: ",N);
	float *b = new float[N-1];
	float *e = new float[N-1];

	for (i = 0; i < N; i++)
	{
		scanf("%f", &b[i]);
	}
	for (i = 0; i < n; i++)
	{
		e[2*i] = b[i];
		e[2*i+1] = b[i+n];
	}
	printf("Начальная последовательность:\t");
	for (i = 0; i < N; i++)
	{
		printf("%5.2f ", b[i]);
	}
	printf("\nПолученная последовательность:\t");
	for (i = 0; i < N; i++)
	{
		printf("%5.2f ", e[i]);
	}
	printf("\n");
	system("pause");
	return 0;
}