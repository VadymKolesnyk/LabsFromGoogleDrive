#include <iostream>
#include <Windows.h>
#include <ctime>
#include <cstdlib>
using namespace std;

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

	int j = 0, i = 0, min = 0;

	for (j = 0; j < N - 1; j++)
	{
		min = a[j];
		for (i = j + 1; i < N; i++)
		{
			if (min > a[i])
			{
				a[j] = a[i];
				a[i] = min;
				min = a[j];
			}
		}
	}


	for (int i = 0; i < N; i++)
	{
		cout << a[i] << "  ";
	}
	cout << endl;
	system("pause");
	return 0;
}