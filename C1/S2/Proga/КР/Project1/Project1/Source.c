//Задача 1. Вариант 2 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

int count(int *a, int n)
{
	int r = 0;
	for (int i = 0; i < n; i++)
		if (!a[i])
			r++;
	return r;
}
void swap(int *a, int *b, int n)
{
	int temp;
	for (int i = 0; i < n; i++)
	{
		temp = a[i];
		a[i] = b[i];
		b[i] = temp;
	}
}
void printmatrix(int**A,int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++) 
		{
			printf("%3d ", A[i][j]);
		}
		printf("\n");
	}
}
int main()
{
	SetConsoleOutputCP(1251);
	printf("Введите размерность матрицы: n = ");
	int n;
	scanf("%d", &n);
	int **A;
	A = (int**)malloc(sizeof(int*) * n);
	for (int i = 0; i < n; i++)
		A[i] = (int*)malloc(sizeof(int) * n);
	printf("Введите элементы матрицы через пробел:\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			scanf("%d", &A[i][j]); 
		}
	}
	printf("Исходная матрица:\n");
	printmatrix(A, n);
	printf("\n");
	int *c;
	c = (int*)malloc(sizeof(int) * n);
	printf("Количество нулей по строчкам:\n");
	for (int i = 0; i < n; i++)
	{
		c[i] = count(A[i], n);
		printf("%d) %d\n", i+1, c[i]);
	}
	printf("\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (count(A[i], n) < count(A[j], n))
			{
				swap(A[i], A[j], n);
			}
		}
	}
	printf("Конечная матрица:\n");
	printmatrix(A, n);
	system("pause");
	return 0;
}