#include <Windows.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
const int D = 3;
long long c = 0, d = 0; // c - сравнение, d - обмен

int best_array(int a[], int N) // массив по возростанию
{
	int i;
	for (i = 0; i < N; i++) a[i] = i;
	return 0;
}
int worst_array(int a[], int N) // массив по убыванию
{
	int i;
	for (i = 0; i < N; i++) a[i] = N - 1 - i;
	return 0;
}
int avg_array(int a[], int N) // случайный массив
{
	int i;
	srand(time(NULL));
	for (i = 0; i < N; i++)
		a[i] = rand() % (int)pow(10, D);
	return 0;
}
int printf_array(int a[], int N) // вывод массива
{
	int i;
	for (i = 0; i < N; i++) printf("%4d ", a[i]);
	printf("\n\n");
	return 0;
}

int rank(int q, int r)
{
	for (int i = r; i > 0; i--)
	{
		q = q / 10;
	}
	q = q % 10;
	return q;
}

int counting_rank(int a[], int N, int i)
{
	int *b = new int[N];
	int C[10] = { 0,0,0,0,0,0,0,0,0,0 }, j;
	for (j = 0; j < N; j++)
	{
		int r = rank(a[j], i);
		C[r] = C[r] + 1;
	}
	for (j = 1; j < 10; j++)
	{
		C[j] = C[j - 1] + C[j];
	}
	for (j = N - 1; j >= 0; j--)
	{
		int r = rank(a[j], i);
		b[C[r] - 1] = a[j];
		C[r]--;
	}
	for (j = 0; j < N; j++)
	{
		d++;
		a[j] = b[j];
	}
	return 0;
}

int radix_sort(int a[], int d, int N)
{
	for (int i = 0; i < d; i++)
	{
		counting_rank(a, N, i);
	}
	return 0;
}

int main()
{
	SetConsoleOutputCP(1251);
	int N, variant;
	printf("Введите количество элементов последовательности n=");
	scanf_s("%d", &N);
	int* a = new int[N];
	printf("Введите вид последовательности (1 - наилучший , 2 - случайный , 3 - наихудший)\n");
	scanf_s("%d", &variant);
	if (variant == 1)
	{
		best_array(a, N);
	}
	else if (variant == 2)
	{
		avg_array(a, N);
	}
	else if (variant == 3)
	{
		worst_array(a, N);
	}
	else
	{
		printf("Введено некорректное значение\n");
		system("pause");
		exit(variant);
	}
	printf("Полученная последовательность:\n");
	printf_array(a, N);

	radix_sort(a, D, N);

	printf_array(a, N);
	printf("Количество сравнений:%lld\nКоличество обменов:%lld\n\n", c, d);
	system("pause");
	return 0;
}