#include <stdio.h>
#include <Windows.h>

int main()
{
	int N;
	scanf_s("%d", &N);
	if (N % 2 == 0)
	{
		N++;
	}
	int c = N / 2;
	char** a = new char*[N];
	for (int i = 0; i < N; i++)
		a[i] = new char[N];
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (((i - c)*(i - c) + (j - c)*(j - c) - c * c > -N/2) && ((i - c)*(i - c) + (j - c)*(j - c) - c * c <= N/2))
			{
				a[i][j] = '*';
			}
			else
			{
				a[i][j] = ' ';
			}
		}
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			printf("%c", a[i][j]);
		}
		printf("\n");
	}
	system("pause");
}