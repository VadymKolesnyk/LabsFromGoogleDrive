//Автор - Коленик Вадим
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <Windows.h>

void main() 
{
	SetConsoleOutputCP(1251);
	int i, j, N, max, max_i;
	printf("Введите порядок матрицы n=");
	scanf_s("%d", &N);
	printf("\n");
	int** m = new int*[N];
	for (i = 0; i < N; i++)
		m[i] = new int[N];
	srand(time(NULL));
	for (i = 0; i < N; i++) 
		for (j = 0; j < N; j++) 
			m[i][j] = rand() % 100;
	printf("Случайная матрица %d на %d:\n\n",N ,N);
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
			printf("%2d  ", m[i][j]);
		printf("\n\n");
	}
	max = m[0][0];
	max_i = 0;
	for (i = 1; i < N; i++)
		if (m[i][i] > max)
		{
			max = m[i][i];
			max_i = i;
		}
	printf("max=m[%d][%d]=%d\n\n",max_i+1,max_i+1,max);
	for (i = max_i; i < N - 1; i++)
		for (j = 0; j < N; j++)
			m[j][i] = m[j][i + 1];
	for (i = max_i; i < N - 1; i++)
		for (j = 0; j < N - 1; j++)
			m[i][j] = m[i + 1][j];
	printf("Матрица %d на %d, полученная удалением %d столбика и %d строчки:\n\n", N-1, N-1,max_i+1,max_i+1);
	for (i = 0; i < N - 1; i++)
	{
		for (j = 0; j < N - 1; j++)
			printf("%2d  ", m[i][j]);
		printf("\n\n");
	}	
	system("pause");
}