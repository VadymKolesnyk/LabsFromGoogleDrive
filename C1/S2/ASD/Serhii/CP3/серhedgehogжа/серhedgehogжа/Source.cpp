#include <ctime>
#include <thread>
#include <iostream>
#include <Windows.h>

using namespace std;

void func(int **arr, int n_1, int n_2, int m)
{
	int i = n_1;
	while (i < n_2)
	{
		int L = 0, R = m - 1, k = 0, j = 0, temp;
		while (L < R)
		{
			int j = L;
			while (j < R)
			{
				if (arr[i][j] < arr[i][j + 1])
				{
					temp = arr[i][j];
					arr[i][j] = arr[i][j + 1];
					arr[i][j + 1] = temp;
					k = j;
				}
				j++;
			}
			R = k;
			j = R - 1;
			while (j >= L)
			{
				if (arr[i][j] < arr[i][j + 1])
				{
					temp = arr[i][j];
					arr[i][j] = arr[i][j + 1];
					arr[i][j + 1] = temp;
					k = j;
				}
				j--;
			}
			L = k + 1;
		}
		i++;
	}
}

void fillarray(int **arr, int n)
{
	for (int i = 0; i < n; i++) 
		for (int j = 0; j < n; j++) 
			arr[i][j] = rand() % 100;
}

void printarray(int **arr, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << arr[i][j] << "\t";
		cout << endl;
	}
}

int main()
{
	SetConsoleOutputCP(1251);
	clock_t begin, end;
	int n;
	cout << "Введите размерность массива: ";
	cin >> n;
	int **arr = new int*[n];
	for (int i = 0; i < n; i++)
		arr[i] = new int[n];
	srand(n);
	cout << "Однопотоковая реализация" << endl;
	fillarray(arr, n);
	//printarray(arr, n);
	cout << endl;
	begin = clock();
	func(arr, 0, n, n);
	end = clock();
	//printarray(arr, n);
	cout << "Затраченное время: " << end - begin << "ms" << endl << endl;
	cout << "-------------------------------------------------------------------------" << endl << endl;
	cout << "Многопотоковая реализация" << endl;
	srand(n);
	fillarray(arr, n);
	//printarray(arr, n);
	cout << endl;
	begin = clock();
	thread potok1(func, arr, 0, n / 2, n);
	thread potok2(func, arr, n/2, n, n);
	potok1.join();
	potok2.join();
	end = clock();
	//printarray(arr, n);
	cout << "Затраченное время: " << end - begin << "ms" << endl;
	system("pause");
}