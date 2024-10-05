#include <iostream>
#include <Windows.h>
#include <ctime>
#include <cstdlib>

using namespace std;

int Merge(int a[], int left, int m, int right)
{
	int n_l = m - left + 2, n_r = right - m + 1;
	int i, j = 0, k = 0;
	int* L = new int[n_l];
	int* R = new int[n_r];
	k = left;
	for (i = 0; k < m + 1; i++, k++)
		L[i] = a[k];

	for (j = 0; k < right + 1; j++, k++)
		R[j] = a[k];

	L[i] = R[j] = MAXINT;

	for (i = 0, j = 0, k = left; k <= right; k++)
	{
		if (L[i] < R[j])
		{
			a[k] = L[i];
			i++;
		}
		else 
		{
			a[k] = R[j];
			j++;
		}
	}
	return 0;
}

int Merge_sort(int a[], int left, int right)
{
	int m;
	if (left < right)
	{
		m = (left + right) / 2;
		Merge_sort(a, left, m);
		Merge_sort(a, m + 1, right);
		Merge(a, left, m, right);
		return 0;
	}
}

int main()
{
	SetConsoleOutputCP(1251);
	int N;
	cout << "Введите количество элементов последовательности n=";
	cin >> N;
	int* a = new int[N];
	srand(time(NULL));
	cout << "Случайная последовательность:" << endl;
	for (int i = 0; i < N; i++)
	{
		a[i] = (rand() % 90) + 10;
		cout << a[i] << "  ";
	}
	cout << endl;
	Merge_sort(a, 0, N - 1);
	for (int i = 0; i < N; i++)
	{
		cout << a[i] << "  ";
	}
	cout << endl;
	system("pause");
	return 0;
}