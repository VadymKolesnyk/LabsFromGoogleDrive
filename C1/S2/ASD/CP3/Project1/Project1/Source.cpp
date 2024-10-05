#include <iostream>
#include <thread>
#include <ctime>
//#define OUTPUT

using namespace std;

int number(int i, int j, int n)
{
	if (j % 2)
		return j * n + i;
	else
		return j * n + n - i - 1;
}
void onethread(int **a, int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)					
		{											
			a[i][j] = number(i, j, n);
		}
}
void firstthread(int **a, int n)
{
	for (int i = 0; i < n/2; i++)
		for (int j = 0; j < n; j++)
		{
			a[i][j] = number(i, j, n);
		}
}

void secondthread(int **a, int n)
{
	for (int i = n / 2; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			a[i][j] = number(i, j, n);
		}
}
void printarray(int **a, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
  
}
int main()
{
	cout << "Enter n = ";
	int n;
	cin >> n;
	int **a = new int*[n];
	for (int i = 0; i < n; i++)
		a[i] = new int[n];
	cout << "1 - One thread" << endl;
	cout << "2 - Multi thread" << endl;
	int v;
	cin >> v;
	clock_t start, stop;
	if (v == 1)
	{
		start = clock();
		onethread(a, n);
		stop = clock();
#ifdef OUTPUT
		printarray(a, n);
#endif // OUTPUT
		cout << "Spent time is " << stop - start << "ms" << endl;
	}
	else if (v == 2)
	{
		start = clock();
		thread t1(firstthread, a, n);
		thread t2(secondthread, a, n);
		t1.join();
		t2.join();
		stop = clock();
#ifdef OUTPUT
		printarray(a, n);
#endif // OUTPUT
		cout << "Spent time is " << stop - start << "ms" << endl;
	}
	system("pause");
	return 0;
}