//����� - ������� �����
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void main()
{
	SetConsoleOutputCP(1251);
	int n, k;
	printf("������� n = ");
	scanf_s("%d", &n);
	n = n * n;
	printf("n^2 = %d\n",n);
	k = n % 10;
	while (n != 0 && k != 3)
	{
		n = n / 10;
		k = n % 10;
	}
	if (k == 3)
		printf("������ � ����� ����������.\n");
	else
		printf("������ � ����� �� ����������.\n");
	system("pause");
}