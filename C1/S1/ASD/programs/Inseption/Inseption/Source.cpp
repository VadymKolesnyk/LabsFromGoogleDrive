#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <ctime>
using namespace std;

int main()
{
	int N;
	SetConsoleOutputCP(1251);
	cout << "Введите количество елементов N=";
	cin >> N;
	int* m = new int[N];
	srand(time(NULL));
	cout << "Случайная последовательность:" << endl;
	for (int i = 0; i < N; i++)
	{
		m[i] = rand()%100;
		cout.width(3);
		cout << m[i] << " ";
	}
	cout << "\n";

	int i, j, key;
	for (j = 1; j < N; j++)
	{
		i = j - 1;
		key = m[j];
		while ((key < m[i]) && (i >= 0))
		{
			m[i + 1] = m[i];
			i--;
		}
		m[i + 1] = key;
	}
	for (i = 0; i < N; i++)
	{
		cout.width(3);
		cout << m[i] << " ";
	}
	cout << "\n";
	system("pause");
}