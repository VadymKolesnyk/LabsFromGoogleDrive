//Автор - Коленик Вадим
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <math.h>

int main()
{
	SetConsoleOutputCP(1251);
	int x = 0, i = 0, j = 0, N = 0;
	bool z = 0;
	printf("Введите порядок матрицы n=");
	scanf_s("%d", &N);
	int** m = new int*[N];
	for (i = 0; i < N; i++)
		m[i] = new int[N];
	int* b = new int[N];
	for (i = 0; i < N; i++)
		b[i] = 0;
	srand(time(NULL));
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
		{
			x = rand() % 10;
			z = rand() % 2;
			m[i][j] = x * pow(-1, z);
		}
	printf("Случайная матирца %d на %d:\n\n", N, N);
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			printf("%3d ", m[i][j]);
		}
		printf("\n\n");
	}
	for (i = 0; i < N; i++)
	{
		z = 0;
		for (j = N - 1; j >= 0; --j)
		{
			if (z) b[i] = b[i] + m[i][j];
			else if (m[i][j] < 0) z = 1;
		}
		if (!z)	b[i] = -1;
	}
	for (i = 0; i < N; i++)
		printf("b[%d] = %4d\n", i + 1, b[i]);
	system("pause");
	return 0;
}