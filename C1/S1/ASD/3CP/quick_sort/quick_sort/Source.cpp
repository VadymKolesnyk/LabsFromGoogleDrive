#include <Windows.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
//#pragma comment(linker, "/STACK:66777216")

long long c = 0, d = 0; // c - ���������, d - �����

int best_array(int a[], int N) // ������ �� �����������
{
	int i;
	for (i = 0; i < N; i++) a[i] = i;
	return 0;
}
int worst_array(int a[], int N) // ������ �� ��������
{
	int i;
	for (i = 0; i < N; i++) a[i] = N - 1 - i;
	return 0;
}
int avg_array(int a[], int N) // ��������� ������
{
	int i;
	srand(time(NULL));
	for (i = 0; i < N; i++)
		a[i] = rand() % 1000;
	return 0;
}
int printf_array(int a[], int N) // ����� �������
{
	int i;
	for (i = 0; i < N; i++) printf("%4d ", a[i]);
	printf("\n\n");
	return 0;
}

int partition(int a[], int left, int right) 
{
	int j, i = left - 1, key = a[right], temp;
	for (j = left; j < right; j++)
	{
		c++;
		if ((a[j] <= key) && (++i != j))
		{
			d++;
			temp = a[i];
			a[i] = a[j];
			a[j] = temp;
		}
	}
	i++;
	d++;
	a[right] = a[i];
	a[i] = key;
	
	return i;
}

int quick_sort(int a[], int left, int right)
{
	int q;
	if (left < right)
	{
		q = partition(a, left, right);
		quick_sort(a, left, q - 1);
		quick_sort(a, q + 1, right);
	}
	return 0;
}

int main()
{
	SetConsoleOutputCP(1251);
	int N, variant;
	printf("������� ���������� ��������� ������������������ n=");
	scanf_s("%d", &N);
	int* a = new int[N];
	printf("������� ��� ������������������ (1 - ��������� , 2 - ��������� , 3 - ���������)\n");
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
		printf("������� ������������ ��������\n");
		system("pause");
		exit(variant);
	}
	printf("���������� ������������������:\n");
	printf_array(a, N);
	quick_sort(a, 0, N - 1);
	printf_array(a, N);
	printf("���������� ���������:%lld\n���������� �������:%lld\n\n", c, d);
	system("pause");
	return 0;
}