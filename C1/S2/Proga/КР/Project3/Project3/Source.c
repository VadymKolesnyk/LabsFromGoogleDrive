//Задача 3. Вариант 2 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#define n 3
#define m 4

int main()
{
	int p = 1, sum = 0;
	SetConsoleOutputCP(1251);
	int A[n][m] = { {2,2,2,2},
					{2,2,2,2},
					{2,2,2,2} };
	printf("Исходная матрица:\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			printf("%3d ", A[i][j]);
		}
		printf("\n");
	}
	for (int i = 0; i < n; i++)
	{
		p = 1;
		for (int k = 0; k < m; k++)
		{
			p = p * A[i][k];
		}
		for (int k = 0; k < m; k++)
		{
			p = p + A[i][k];
		}
		sum = sum + p;
	}
	printf("Сумма = %d\n", sum);
	system("pause");
	return 0;
}