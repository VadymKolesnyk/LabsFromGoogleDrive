#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <io.h>


typedef struct // ��������� ����������
{
	char name[10];
	char group[10];
}faculty;

typedef struct // ��������� ��������
{
	char name[15];
	int math, prog, phis;
}student;

typedef struct // ��������� ������
{
	faculty fac;
	student stud;
	int year;
}record;

void add(record rec, FILE *f) // �������� ������ � ����
{
	int n;
	fseek(f, 0, SEEK_SET);
	fread(&n, sizeof(n), 1, f);// ���������� ���������� �������
	n++;
	fseek(f, 0, SEEK_SET);
	fwrite(&n, sizeof(n), 1, f);// ���������� �������� ������� (n+1)
	fseek(f, 0, SEEK_END);
	fwrite(&rec, sizeof(rec), 1, f);// ���������� ������ � ����� �����
}
int summa(record rec) // ����� ������
{
	return (rec.stud.math) + (rec.stud.phis) + (rec.stud.prog);
}
void printrecord(record rec) // ���������� ������
{
	printf("%-9s\t%s\t%s\t%d    %d    %d\t%d\t%3.1f\n", rec.stud.name, rec.fac.name, rec.fac.group, rec.stud.math, rec.stud.phis, rec.stud.prog, rec.year, (float)(summa(rec))/3);
}
void readrecord(record *rec) // ������� ������ � ������ � ����������
{
	printf("������� �������: ");
	scanf("%s", ((rec->stud).name));
	printf("������� ���������: ");
	scanf("%s", ((rec->fac).name));
	printf("������� ������: ");
	scanf("%s", ((rec->fac).group));
	printf("������� ������ ����� ������ (����������, ������, ����������������): ");
	scanf("%d", &((rec->stud).math));
	scanf("%d", &((rec->stud).phis));
	scanf("%d", &((rec->stud).prog));
	printf("������� ����: ");
	scanf("%d", &(rec->year));
}
int print(FILE *f) // ���������� ��� ������ �� ����� �� �������
{
	int n;
	record rec;
	fseek(f, 0, SEEK_SET);
	fread(&n, sizeof(n), 1, f); // ���������� ���������� �������
	if (n == 0)
	{
		printf("���� ����\n");
		return 1;
	}
	printf("�\t�������\t\t�����.\t������\t���. ���. ����.\t����\t��.����\n");
	for (int i = 0; i < n; i++)
	{
		printf("%2d)\t", i + 1);
		fread(&rec, sizeof(rec), 1, f);
		printrecord(rec);
	}
	return 0;
}
int del(int t, FILE *f) // �������� ������
{
	int n;
	int k = sizeof(record);
	record rec;
	fseek(f, 0, SEEK_SET);
	fread(&n, sizeof(n), 1, f); // ���������� ���������� �������
	if (n == 0)
	{
		printf("���� ����\n");
		return 1;
	}
	if (t > n || t < 1)
	{
		printf("������ ������ �� ����������\n");
		return 1;
	}
	fseek(f, k * t, SEEK_CUR); // ������� � ������ ������ 
	for (int i = t; i < n; i++) // ����� ���� ������� ����� ��������� �� 1 �����
	{
		if (fread(&rec, k, 1, f))
		{
			fseek(f, -2 * k, SEEK_CUR);
			fwrite(&rec, k, 1, f);
			fseek(f, k, SEEK_CUR);
		}
	}
	fseek(f, 0, SEEK_SET);
	n--;
	fwrite(&n, sizeof(n), 1, f); // ���������� ���������� �������
	_chsize(_fileno(f), sizeof(n) + n * k); // ������� �����
	return 0;
}

int edit(int t, FILE *f) // �������������� ������
{
	int n;
	int k = sizeof(record);
	record rec;
	fseek(f, 0, SEEK_SET);
	fread(&n, sizeof(n), 1, f); // ���������� ���������� �������
	if (n == 0)
	{
		printf("���� ����\n");
		return 1;
	}
	if (t > n || t < 1)
	{
		printf("������ ������ �� ����������\n");
		return 1;
	}
	fseek(f, k * (t - 1), SEEK_CUR); // ������� � ������ ������ 
	fread(&rec, k, 1, f);
	printf("�������� ��� ������ �������\n");
	printf("1 - �������\n");
	printf("2 - ���������\n");
	printf("3 - ������\n");
	printf("4 - ������\n");
	printf("5 - ����\n");
	int v = -1;
	scanf("%d", &v);
	switch (v)
	{
	case 1:
	{
		printf("������� �������: ");
		scanf("%s", (rec.stud.name));
				break;
	}
	case 2:
	{
		printf("������� ���������: ");
		scanf("%s", (rec.fac.name));
		break;
	}
	case 3:
	{
		printf("������� ������: ");
		scanf("%s", (rec.fac.group));
		break;
	}
	case 4:
	{
		printf("�������� �������\n");
		printf("1 - ����������\n");
		printf("2 - ������\n");
		printf("3 - ����������������\n");
		int s = -1;
		scanf("%d", &s);
		switch (s)
		{
		case 1:
		{
			printf("������� ������: ");
			scanf("%d", &(rec.stud.math));
			break;
		}
		case 2:
		{
			printf("������� ������: ");
			scanf("%d", &(rec.stud.phis));
			break;
		}
		case 3:
		{
			printf("������� ������: ");		
			scanf("%d", &(rec.stud.prog));
			break;
		}
		default:
			break;
		}
		break;
	}
	case 5:
	{
		printf("������� ����: ");
		scanf("%d", &(rec.year));
		break;
	}
	default:
		break;
	}
	fseek(f, -k, SEEK_CUR); // ������� � ������ ���������� ������
	fwrite(&rec, k, 1, f); // ���������� �� � ����
	printf("��������� ������� �������");
	return 0;
}
int sort(FILE *f) // ���������� �������
{
	int n;
	int k = sizeof(record);
	record rec1, rec2;
	fseek(f, 0, SEEK_SET);
	fread(&n, sizeof(n), 1, f); // ���������� ���������� �������
	if (n == 0)
	{
		printf("���� ����\n");
		return 1;
	}
	for (int j = 0; j < n - 1 ; j++) // ���������� ������ ��������
	{
		int max = j;
		for (int i = j + 1; i < n; i++)
		{
			fseek(f, sizeof(n) + k * max, SEEK_SET);
			fread(&rec1, k, 1, f);
			fseek(f, sizeof(n) + k * i, SEEK_SET);
			fread(&rec2, k, 1, f);
			if (summa(rec1) < summa(rec2))
			{
				max = i;
			}
		}
		fseek(f, sizeof(n) + k * j, SEEK_SET); // ������������ ���� ������� �������
		fread(&rec1, k, 1, f);
		fseek(f, sizeof(n) + k * max, SEEK_SET);
		fread(&rec2, k, 1, f);
		fseek(f, sizeof(n) + k * max, SEEK_SET);
		fwrite(&rec1, k, 1, f);
		fseek(f, sizeof(n) + k * j, SEEK_SET);
		fwrite(&rec2, k, 1, f);
	}
	return 0;
}
int exel(FILE *f) // ����� �� ����� ������� ����������
{
	int n;
	record rec;
	fseek(f, 0, SEEK_SET);
	fread(&n, sizeof(n), 1, f); // ���������� ���������� �������
	if (n == 0)
	{
		printf("���� ����\n");
		return 1;
	}
	printf("�\t�������\t\t�����.\t������\t���. ���. ����.\t����\tC�.����\n");
	for (int i = 0; i < n; i++)
	{

		fread(&rec, sizeof(rec), 1, f);
		int sum = summa(rec);
		if (sum > 13) //�������� ������� ���� ������ 4,5
		{
			printf("%2d)\t", i + 1);
			printrecord(rec);
		}
	}
	return 0;
}

int delF(FILE *f) // �������� ����������
{
	int n;
	record rec;
	fseek(f, 0, SEEK_SET);
	fread(&n, sizeof(n), 1, f); // ���������� ���������� �������
	if (n == 0)
	{
		printf("���� ����\n");
		return 1;
	}
	int k = sizeof(record);
	for (int i = 0; i < n; i++) // ����� �� �����
	{

		fread(&rec, sizeof(rec), 1, f);
		if (rec.stud.math < 3 || rec.stud.phis < 3 || rec.stud.prog < 3) // �������� ���� �� ���� �� 1 ������ ������ 3
		{
			printf("%s ��������. ������: %d %d %d\n", rec.stud.name, rec.stud.math, rec.stud.phis, rec.stud.prog);
			for (int j = i; j < n; j++)
			{
				if (fread(&rec, k, 1, f)) // ����� ���� ������� ����� ��������� �� 1 �����
				{
					fseek(f, -2 * k, SEEK_CUR);
					fwrite(&rec, k, 1, f);
					fseek(f, k, SEEK_CUR);
				}
			}
			fseek(f, 0, SEEK_SET);
			n--;
			fwrite(&n, sizeof(n), 1, f);// ���������� ���������� �������
			_chsize(_fileno(f), sizeof(n) + n * k); // ������� �����
			fseek(f, sizeof(n) + i-- * k, SEEK_SET); // ������� � ��������� ������, ����� ���������
		}
	}
	return 0;
}

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	FILE *f = fopen("data.bin", "r+b"); //��������� ���� ��� ������ � ������
	if (!f) // ���� ����� �� ����������
	{
		f = fopen("data.bin", "w+b"); // ������� ���� ��� ������ � ������
		if (!f)
		{
			printf("Error\n");
			system("pause");
			return 1;
		}
		int n = 0;
		fwrite(&n, sizeof(n), 1, f); // � ���������, ��� ��� ��������� ������ 0 �������
	}
	int v = -1;
	while (v) // ����
	{
		printf("0 - �����\n");
		printf("1 - �������� ��������\n");
		printf("2 - ������� ������ ��������\n");
		printf("3 - �������� ������ ��������\n");
		printf("4 - ������� ����������, � ������� ������� ���� ������ 4,5\n");
		printf("5 - ��������� ����������\n");
		printf("6 - ������������� �� ���������� �������� �����\n");
		printf("7 - ����� ���� ������� �� �����\n");
		scanf("%d", &v);
		switch (v)
		{
		case 1:
		{
			record rec;
			readrecord(&rec);
			add(rec, f);
				break;
		}
		case 2:
		{
			if (!print(f)) // print(f) ���������� 1 ���� ���� ����
			{
				printf("�������� ����� ��������: ");
				int s;
				scanf("%d", &s);
				del(s, f);
			}
			break;
		}
		case 3:
		{
			if (!print(f)) // print(f) ���������� 1 ���� ���� ����
			{
				printf("�������� ����� ���������: ");
				int s;
				scanf("%d", &s);
				edit(s, f);
			}
			break;
		}
		case 4:
		{
			exel(f);
			break;
		}
		case 5:
		{
			delF(f);
			break;
		}
		case 6:
		{
			sort(f);
			break;
		}
		case 7:
		{
			print(f);
			break;
		}
		default:
		{
			printf("������� ����� �� 0 �� 7\n");
			break;
		}
		}
	}
	fclose(f);
}