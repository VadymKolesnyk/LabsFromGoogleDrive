#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "stacksllist.h" // ���� � ����������� ������
#include "stackdllist.h" // ���� � ���������� ������
#include "queuedllist.h" // ������� � ������������ � ���������� ������

int main()
{
	SetConsoleOutputCP(1251);
	int v = -1;
	while (v)
	{
		printf("0 - ����� �� ��������\n");
		printf("1 - ���� � ����������� ������\n");
		printf("2 - ���� � ���������� ������\n");
		printf("3 - ������� � ������������ � ���������� ������\n");
		scanf("%d", &v);
		system("cls");
		if (v == 1)
		{
			stacks *st = initsls(); // ������������� �����
			int s = -1;
			if (!st)
			{
				printf("�� ������� �������� ������ ��� ����\n");
				s = 0;
			}
			while (s)
			{
				printf("0 - �����\n");
				printf("1 - �������� � ����\n");
				printf("2 - ������� �� �����\n");
				printf("3 - ������ �����\n");
				printf("4 - �������� ����\n");
				scanf("%d", &s);
				system("cls");
				if (s == 1)
				{
					printf("������� �����, key=");
					int key;
					scanf("%d", &key);
					if (addsls(st, key) == 2) // ���������� � ����
					{
						printf("�� ������� �������� ������ ��� �������\n");
					}
					else
					{
						printf("%d �������� � ����\n", key);
					}
				}
				else if (s == 2)
				{
					int key = 0;
					if (delsls(st, &key) == 2) // �������� �� �����
					{
						printf("C��� ����\n");
					}
					else
					{
						printf("%d ������ �� �����\n", key);
					}
				}
				else if (s == 3)
				{
					if (printsls(st) == 2) // ����� �� ����� �����
					{
							printf("C��� ����\n");
					}
				}
				else if (s == 4)
				{
					clearsls(st); // �������� �����
					printf("C��� ������\n");
				}
			}
			freesls(st); // ������� ����
		}
		else if (v == 2)
		{
			stackd *st = initdls(); // ������������� �����
			int s = -1;
			if (!st)
			{
				printf("�� ������� �������� ������ ��� ����\n");
				s = 0;
			}
			while (s)
			{
				printf("0 - �����\n");
				printf("1 - �������� � ����\n");
				printf("2 - ������� �� �����\n");
				printf("3 - ������ �����\n");
				printf("4 - �������� ����\n");
				scanf("%d", &s);
				system("cls");
				if (s == 1)
				{
					printf("������� �����, key=");
					int key;
					scanf("%d", &key);
					if (adddls(st, key) == 2) // ���������� � ����
					{
						printf("�� ������� �������� ������ ��� �������\n");
					}
					else
					{
						printf("%d �������� � ����\n", key);
					}
				}
				else if (s == 2)
				{
					int key = 0;
					if (deldls(st, &key) == 2) // �������� �� �����
					{
						printf("C��� ����\n");
					}
					else
					{
						printf("%d ������ �� �����\n", key);
					}
				}
				else if (s == 3)
				{
					if (printdls(st) == 2) // ����� �� ����� �����
					{
						printf("C��� ����\n");
					}
				}
				else if (s == 4)
				{
					cleardls(st); // �������� �����
					printf("C��� ������\n");
				}
			}
			freedls(st); // ������� ����
		}
		else if (v == 3)
		{
			queue *q = initq(); // ������������� �������
			int s = -1;
			if (!q)
			{
				printf("�� ������� �������� ������ ��� �������\n");
				s = 0;
			}
			while (s)
			{
				printf("0 - �����\n");
				printf("1 - �������� � �������\n");
				printf("2 - ������� �� �������\n");
				printf("3 - ������ �������\n");
				printf("4 - �������� �������\n");
				scanf("%d", &s);
				system("cls");
				if (s == 1)
				{
					printf("������� �����, key=");
					int key;
					scanf("%d", &key);

					int p = 0;
					while (p != 1 && p != 2 && p != 3)
					{
						printf("�������� ���������:\n");
						printf("1 - ������\n");
						printf("2 - �������\n");
						printf("3 - �������\n");
						scanf("%d", &p);
					}
					if (addq(q, key, p) == 2) // ���������� � �������
					{
						printf("�� ������� �������� ������ ��� �������\n");
					}
					else
					{
						printf("%d �������� � �������\n", key);
					}
				}
				else if (s == 2)
				{
					int key = 0;
					if (delq(q, &key) == 2) // �������� �� �������
					{
						printf("������� �����\n");
					}
					else
					{
						printf("%d ������ �� �������\n", key);
					}
				}
				else if (s == 3)
				{
					if (printq(q) == 2) // ����� ������� �� �����
					{
						printf("������� �����\n");
					}
				}
				else if (s == 4)
				{
					clearq(q); // ������� �������
					printf("������� �������\n");
				}
			}
			freeq(q); // ������� �������
		}
	}
	return 0;
}
