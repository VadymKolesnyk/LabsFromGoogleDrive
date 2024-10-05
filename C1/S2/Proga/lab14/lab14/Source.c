#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <io.h>


typedef struct // структура факультета
{
	char name[10];
	char group[10];
}faculty;

typedef struct // структура студента
{
	char name[15];
	int math, prog, phis;
}student;

typedef struct // структура записи
{
	faculty fac;
	student stud;
	int year;
}record;

void add(record rec, FILE *f) // добавить запись в файл
{
	int n;
	fseek(f, 0, SEEK_SET);
	fread(&n, sizeof(n), 1, f);// считывание количества записей
	n++;
	fseek(f, 0, SEEK_SET);
	fwrite(&n, sizeof(n), 1, f);// перезапись колества записей (n+1)
	fseek(f, 0, SEEK_END);
	fwrite(&rec, sizeof(rec), 1, f);// добавление записи в конец файла
}
int summa(record rec) // сумма баллов
{
	return (rec.stud.math) + (rec.stud.phis) + (rec.stud.prog);
}
void printrecord(record rec) // напичатать запись
{
	printf("%-9s\t%s\t%s\t%d    %d    %d\t%d\t%3.1f\n", rec.stud.name, rec.fac.name, rec.fac.group, rec.stud.math, rec.stud.phis, rec.stud.prog, rec.year, (float)(summa(rec))/3);
}
void readrecord(record *rec) // считать данные в запись с клавиатуры
{
	printf("Введите фамилию: ");
	scanf("%s", ((rec->stud).name));
	printf("Введите факультет: ");
	scanf("%s", ((rec->fac).name));
	printf("Введите группу: ");
	scanf("%s", ((rec->fac).group));
	printf("Введите оценки через пробол (математика, физика, программирование): ");
	scanf("%d", &((rec->stud).math));
	scanf("%d", &((rec->stud).phis));
	scanf("%d", &((rec->stud).prog));
	printf("Введите курс: ");
	scanf("%d", &(rec->year));
}
int print(FILE *f) // напечатать все записи из файла по порядку
{
	int n;
	record rec;
	fseek(f, 0, SEEK_SET);
	fread(&n, sizeof(n), 1, f); // считывание количества записей
	if (n == 0)
	{
		printf("Файл пуст\n");
		return 1;
	}
	printf("№\tФамилия\t\tФакул.\tГруппа\tмат. физ. прог.\tКурс\tСр.балл\n");
	for (int i = 0; i < n; i++)
	{
		printf("%2d)\t", i + 1);
		fread(&rec, sizeof(rec), 1, f);
		printrecord(rec);
	}
	return 0;
}
int del(int t, FILE *f) // удаление записи
{
	int n;
	int k = sizeof(record);
	record rec;
	fseek(f, 0, SEEK_SET);
	fread(&n, sizeof(n), 1, f); // считывание количества записей
	if (n == 0)
	{
		printf("Файл пуст\n");
		return 1;
	}
	if (t > n || t < 1)
	{
		printf("Такого номера не существует\n");
		return 1;
	}
	fseek(f, k * t, SEEK_CUR); // переход к нужной записи 
	for (int i = t; i < n; i++) // сдвиг всех написей после удаляемой на 1 назад
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
	fwrite(&n, sizeof(n), 1, f); // перезапись количества записей
	_chsize(_fileno(f), sizeof(n) + n * k); // обрезка файла
	return 0;
}

int edit(int t, FILE *f) // редактирование записи
{
	int n;
	int k = sizeof(record);
	record rec;
	fseek(f, 0, SEEK_SET);
	fread(&n, sizeof(n), 1, f); // считывание количества записей
	if (n == 0)
	{
		printf("Файл пуст\n");
		return 1;
	}
	if (t > n || t < 1)
	{
		printf("Такого номера не существует\n");
		return 1;
	}
	fseek(f, k * (t - 1), SEEK_CUR); // переход к нужной записи 
	fread(&rec, k, 1, f);
	printf("Выберите что хотите изенить\n");
	printf("1 - Фамилия\n");
	printf("2 - Факультут\n");
	printf("3 - Группа\n");
	printf("4 - Оценки\n");
	printf("5 - Курс\n");
	int v = -1;
	scanf("%d", &v);
	switch (v)
	{
	case 1:
	{
		printf("Введите фамилию: ");
		scanf("%s", (rec.stud.name));
				break;
	}
	case 2:
	{
		printf("Введите факультет: ");
		scanf("%s", (rec.fac.name));
		break;
	}
	case 3:
	{
		printf("Введите группу: ");
		scanf("%s", (rec.fac.group));
		break;
	}
	case 4:
	{
		printf("Выберите предмет\n");
		printf("1 - Математика\n");
		printf("2 - Физика\n");
		printf("3 - Программирование\n");
		int s = -1;
		scanf("%d", &s);
		switch (s)
		{
		case 1:
		{
			printf("Введите оценку: ");
			scanf("%d", &(rec.stud.math));
			break;
		}
		case 2:
		{
			printf("Введите оценку: ");
			scanf("%d", &(rec.stud.phis));
			break;
		}
		case 3:
		{
			printf("Введите оценку: ");		
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
		printf("Введите курс: ");
		scanf("%d", &(rec.year));
		break;
	}
	default:
		break;
	}
	fseek(f, -k, SEEK_CUR); // переход к началу изменяемой записи
	fwrite(&rec, k, 1, f); // перезапись ее в файл
	printf("Изменения успешно внесены");
	return 0;
}
int sort(FILE *f) // сортировка записей
{
	int n;
	int k = sizeof(record);
	record rec1, rec2;
	fseek(f, 0, SEEK_SET);
	fread(&n, sizeof(n), 1, f); // считывание количества записей
	if (n == 0)
	{
		printf("Файл пуст\n");
		return 1;
	}
	for (int j = 0; j < n - 1 ; j++) // сортировка прямой вставкой
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
		fseek(f, sizeof(n) + k * j, SEEK_SET); // перестановка двух записей местами
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
int exel(FILE *f) // вывод на экран записей отличников
{
	int n;
	record rec;
	fseek(f, 0, SEEK_SET);
	fread(&n, sizeof(n), 1, f); // считывание количества записей
	if (n == 0)
	{
		printf("Файл пуст\n");
		return 1;
	}
	printf("№\tФамилия\t\tФакул.\tГруппа\tмат. физ. прог.\tКурс\tCр.балл\n");
	for (int i = 0; i < n; i++)
	{

		fread(&rec, sizeof(rec), 1, f);
		int sum = summa(rec);
		if (sum > 13) //проверка средрий балл больше 4,5
		{
			printf("%2d)\t", i + 1);
			printrecord(rec);
		}
	}
	return 0;
}

int delF(FILE *f) // удаление двоечников
{
	int n;
	record rec;
	fseek(f, 0, SEEK_SET);
	fread(&n, sizeof(n), 1, f); // считывание количества записей
	if (n == 0)
	{
		printf("Файл пуст\n");
		return 1;
	}
	int k = sizeof(record);
	for (int i = 0; i < n; i++) // обход по файлу
	{

		fread(&rec, sizeof(rec), 1, f);
		if (rec.stud.math < 3 || rec.stud.phis < 3 || rec.stud.prog < 3) // проверка есть ли хотя бы 1 оценка меньше 3
		{
			printf("%s отчислен. Оценки: %d %d %d\n", rec.stud.name, rec.stud.math, rec.stud.phis, rec.stud.prog);
			for (int j = i; j < n; j++)
			{
				if (fread(&rec, k, 1, f)) // сдвиг всех написей после удаляемой на 1 назад
				{
					fseek(f, -2 * k, SEEK_CUR);
					fwrite(&rec, k, 1, f);
					fseek(f, k, SEEK_CUR);
				}
			}
			fseek(f, 0, SEEK_SET);
			n--;
			fwrite(&n, sizeof(n), 1, f);// перезапись количества записей
			_chsize(_fileno(f), sizeof(n) + n * k); // обрезка файла
			fseek(f, sizeof(n) + i-- * k, SEEK_SET); // переход к следующей записи, после удаленной
		}
	}
	return 0;
}

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	FILE *f = fopen("data.bin", "r+b"); //открываем файл для чтения и записи
	if (!f) // если файла не существует
	{
		f = fopen("data.bin", "w+b"); // создаем файл для чтения и записи
		if (!f)
		{
			printf("Error\n");
			system("pause");
			return 1;
		}
		int n = 0;
		fwrite(&n, sizeof(n), 1, f); // и указываем, что там храниться сейчас 0 записей
	}
	int v = -1;
	while (v) // меню
	{
		printf("0 - выход\n");
		printf("1 - добавить студента\n");
		printf("2 - удалить запись студента\n");
		printf("3 - изменить запись студента\n");
		printf("4 - вывести отличников, у которых средний балл больше 4,5\n");
		printf("5 - отчислить двоечников\n");
		printf("6 - отсортировать по уменьшению среднего балла\n");
		printf("7 - вывод всех записей на экран\n");
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
			if (!print(f)) // print(f) возвращает 1 если файл пуст
			{
				printf("Выберите номер удаления: ");
				int s;
				scanf("%d", &s);
				del(s, f);
			}
			break;
		}
		case 3:
		{
			if (!print(f)) // print(f) возвращает 1 если файл пуст
			{
				printf("Выберите номер изменения: ");
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
			printf("Введите число от 0 до 7\n");
			break;
		}
		}
	}
	fclose(f);
}