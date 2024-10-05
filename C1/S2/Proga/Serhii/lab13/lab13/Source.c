#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>

typedef struct
{
	int A, B, C;
}line;

void main()
{
	SetConsoleOutputCP(1251);
	FILE *f;
	f = fopen("input.txt", "r"); 
	if (f == NULL)
		printf("Не удалось открыть файл\n");
	else
	{
		printf("Файл успешно открыт\n");
		int n = 0, i = 0;
		while (!feof(f))
		{
			char d[100];
			fgets(d, 100, f);
			n++;
		}
		printf("Количество строк в файле: %d", n);
		printf("\n\n");
		line *a = (line*)malloc(n*sizeof(line));
		fclose(f);
		f = fopen("input.txt", "r");
		while (!feof(f))
		{
			fscanf(f, "%d %d %d", &a[i].A, &a[i].B, &a[i].C);
			i++;
		}
		fclose(f);
		f = fopen("output.txt", "w");
		for (i = 0; i < n; i++)
		{
			for (int j = i + 1; j < n; j++)
			{
				if (!(a[i].A * a[j].B - a[i].B * a[j].A) && !(a[i].B * a[j].C - a[i].C * a[j].B))
					fprintf(f, "Прямые с коэффициентами %2d %2d %2d и %2d %2d %2d совпадают\n", a[i].A, a[i].B, a[i].C, a[j].A, a[j].B, a[j].C);
				else if ((a[i].A * a[j].B - a[i].B * a[j].A) == 0)
					fprintf(f, "Прямые с коэффициентами %2d %2d %2d и %2d %2d %2d параллельные\n", a[i].A, a[i].B, a[i].C, a[j].A, a[j].B, a[j].C);
				else if (((a[i].A * a[j].A) + (a[i].B * a[j].B)) == 0)
					fprintf(f, "Прямые с коэффициентами %2d %2d %2d и %2d %2d %2d перпендикулярные\n", a[i].A, a[i].B, a[i].C, a[j].A, a[j].B, a[j].C);
				else
					fprintf(f, "Прямые с коэффициентами %2d %2d %2d и %2d %2d %2d пересекаются\n", a[i].A, a[i].B, a[i].C, a[j].A, a[j].B, a[j].C);
			}
		}
		fclose(f);
		printf("Данные файла:\n");
		for (i = 0; i < n; i++)
		{
			printf("%2d %2d %2d\n", a[i].A, a[i].B, a[i].C);
		}
		printf("Результат работы находится в файле.\n");
	}
	system("pause");
}