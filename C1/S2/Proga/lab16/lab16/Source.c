#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#define begin {
#define end }

#define chislo 0
#define kolichestvo 1

#define OUTPUT

int main()
	begin
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
#define a number
	int n;
#ifdef OUTPUT // ����� ��� ����������� OUTPUT
	printf("������� ���������� ����� � ������ n = ");
#endif // OUTPUT
	scanf("%d", &n);
#ifdef OUTPUT // ����� ��� ����������� OUTPUT
	printf("������� ����� ����� ������:\n");
#endif // OUTPUT
	int *a = (int*)malloc(n * sizeof(int)); // ��������� ������ ��� �����
	for (int i = 0; i < n; i++) // ���� ������ � ����������
		begin
		scanf("%d", &a[i]);
		end
	int **b = (int**)malloc(n * sizeof(int*)); // ��������� ������ ��� ��������������� �����
	for (int i = 0; i < n; i++)
		begin
		b[i] = (int*)malloc(2 * sizeof(int));
		end
	int k = 0;
	for (int i = 0; i < n; i++)
		begin
		int z = 1; // ���� ���� �� ��������� ����� ������� � �������������� �����
		for (int j = 0; j < k; j++)
			begin
			if (a[i] == b[j][chislo])
				begin
				b[j][kolichestvo]++;
				z = 0;
				break;
				end
			end
		if (z)
			begin
			b[k][chislo] = a[i];
			b[k][kolichestvo] = 1;
			k++;
			end
		end
#ifdef OUTPUT // ����� ��� ����������� OUTPUT
	printf("���������� ��������� � ����� ������� �� ���������:\n");
#endif // OUTPUT
	for (int i = 0; i < k; i++) // ����� ���������� ��������� � ����� ������� �� ���������
		begin
		printf("%d  - %d �.\n", b[i][chislo], b[i][kolichestvo]);
		end

#undef a
#define a str
	char a[100];
#ifdef OUTPUT // ����� ��� ����������� OUTPUT
		printf("������� ������ �� 99 ��������:\n");
#endif // OUTPUT
	scanf("%s", a);
#ifdef OUTPUT // ����� ��� ����������� OUTPUT
	printf("������� ��� �������, ������� ���� �����: k = ");
#endif // OUTPUT
	scanf("%d", &n);
	int z = 1; // ���� ������ �� ������
	for (int i = 0; a[i] != '\0'; i++)
		begin
		if (a[i] == n) // ����� �������
			begin
			printf("������ ������ � �������� %d\n", i);
			z = 0;
			break;
			end
		end
	if (z)
		begin
		printf("������ �� ������\n");
		end
	system("pause");
	end