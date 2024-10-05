//Задача 2. Вариант 2 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

int main()
{
	SetConsoleOutputCP(1251);
	char f, g;
	int count = 0;
	FILE* F = fopen("F.txt", "r");
	if (!F)
	{
		printf("Файла F не существует");
		system("pause");
		exit(1);
	}
	FILE* G = fopen("G.txt", "r");
	if (!G)
	{
		printf("Файла F не существует");
		system("pause");
		exit(1);
	}
	int z = 1;
	while (z)
	{
		count++;
		if (feof(F) && feof(G))
		{
			break;
		}
		else if (feof(F) || feof(G))
		{
			z = 0;
		}
		else
		{
			fscanf(F, "%c", &f);
			fscanf(G, "%c", &g);
			if (f != g)
			{
				z = 0;
			}
		}
	}
	fclose(F);
	fclose(G);
	if (z)
	{
		printf("Файлы совпадают\n");
	}
	else
	{
		printf("Файлы отличаются начиная с %d позиции\n", count);
	}
	system("pause");
	return 0;
}