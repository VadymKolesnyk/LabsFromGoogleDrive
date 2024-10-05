#include <Windows.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

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
		a[i] = rand()%1000;
	return 0;
}
int printf_array(int a[], int N) // вывод массива
{
	int i;
	for (i = 0; i < N; i++) printf("%4d ", a[i]);
	printf("\n\n");
	return 0;
}

int selection(int a[], int N) 
{
	int j = 0, i = 0, min = 0, temp = 0;
	for (j = 0; j < N - 1; j++)
	{
		min = j;
		for (i = j + 1; i < N; i++)
		{
			c++;
			if (a[min] > a[i])
			{
				min = i;
			}
		}
		d++;
		temp = a[j];
		a[j] = a[min];
		a[min] = temp;
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
	selection(a, N);
	printf_array(a, N);
	printf("Количество сравнений:%lld\nКоличество обменов:%lld\n\n", c, d);
	system("pause");
	return 0;
}