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

//------------------------------------------------------


	for (int i = 0; i < N; i++)
	{
		cout << a[i] << "  ";
	}
	cout << endl;
	system("pause");
	return 0;
}