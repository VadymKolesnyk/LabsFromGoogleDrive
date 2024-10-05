#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct aircraft
{
	int type; // 1 - самолет, 2 - вертолет, 3 - аэроплан
	int free_seat;
	float ticket_price;
};

typedef struct flight
{
	int number;
	char *date;
};

typedef struct node
{
	struct aircraft *plane;
	struct flight *fl;
};

char* aircraft_type(int t)
{
	if (t == 1)
		return "Самолет";
	if (t == 2)
		return "Вертолет";
	if (t == 3)
		return "Аэроплан";
}

int file_empty(FILE *f)
{
	int l = 0;
	node *a;
	f = fopen("output.bin", "rb");
	l = fread(&a, sizeof(a), 1, f);
	if (!l)
	{
		fclose(f);
		return 1;
	}
	else
	{
		fclose(f);
		return 0;
	}
}

int main()
{
	SetConsoleTitle("Terminal");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	int q = 1, choice = 0, n = 0, i, c;
	int memory = 0;
	FILE *mf = fopen("output.bin", "wb");
	if (!mf)
	{
		printf("FILE_WASNT_OPENED");
		system("pause");
		return 0;
	}
	fclose(mf);
	node **arr = NULL;
	i = 0;
	while (q)
	{
		printf("-------------------------------МЕНЮ-------------------------------\n");
		printf("0 - выход из программы\n");
		printf("1 - добавить информацию о рейсе\n");
		printf("2 - изменить данные в файле\n");
		printf("3 - удалить все данные\n");
		printf("4 - составить список авиационных рейсов, где есть свободные места\n");
		printf("5 - показать рейсы на указанную дату\n");
		printf("6 - отсортировать данные по возрастанию цен билетов по каждой дате\n");
		printf("7 - показать данные\n");
		printf("8 - показать количество записей в файле\n");
		printf("Выберите действие: ");
		scanf("%d", &choice);
		system("cls");
		switch (choice)
		{
		case 0:
		{
			for (int j = 0; j < n; j++)
			{
				if (arr[i])
				{
					free(arr[i]->plane);
					free(arr[i]->fl);
				}
				else
					break;
			}
			free(arr);
			exit(choice);
			break;
		}
		case 1:
		{
			mf = fopen("output.bin", "ab");
			arr = (node**)realloc(arr, memory += sizeof(node*));
			arr[i] = (node*)malloc(sizeof(node));
			(arr[i])->plane = (aircraft*)malloc(sizeof(aircraft));
			(arr[i])->fl = (flight*)malloc(sizeof(flight));
			(arr[i])->fl->date = (char*)malloc(10 * sizeof(char)); 
			printf("Добавление информации\n");
			c = 0;
			while (c != 1 && c != 2 && c != 3)
			{
				printf("1 - самолет\n2 - вертолет\n3 - аэроплан\n");
				printf("Укажите тип: ");
				scanf("%d", &c);
			}
			(arr[i])->plane->type = c;
			printf("Укажите количество свободных мест: ");
			scanf("%d", &((arr[i])->plane->free_seat));
			printf("Укажите стоимость билета: ");
			scanf("%f", &((arr[i])->plane->ticket_price));
			printf("Введите номер рейса: ");
			scanf("%d", &((arr[i])->fl->number));
			printf("Введите дату рейса в формате гггг.мм.дд: ");
			scanf("%s", (arr[i])->fl->date);
			//fgets((arr[i])->fl->date, 10, stdin);
			//fflush(stdin);
			system("cls");
			fwrite(&arr[i], sizeof(node), 1, mf);
			//printf("%d %d %f", (arr[i])->plane->type, (arr[i])->plane->free_seat, (arr[i])->plane->ticket_cost);
			i++;
			fclose(mf);
			break;
		}
		case 2:
		{
			if (file_empty(mf))
			{
				printf("Файл пуст. Невозможно изменить данные\n");
				break;
			}

			node *b;
			int l = 0, k = 0, n1 = 0, n2 = 0;
			mf = fopen("output.bin", "rb");
			l = fread(&b, sizeof(node), 1, mf);
			if (!l)
			{
				printf("Данные отсутствуют\n");
				fclose(mf);
				break;
			}
			printf("№  Тип      Свободные места Цена     Рейс  Дата\n");
			while (l == 1)
			{
				printf("%-2d %-8s %-15d %-8.2f %-5d %-10s\n", ++k, aircraft_type(b->plane->type), b->plane->free_seat, b->plane->ticket_price, b->fl->number, b->fl->date);
				l = fread(&b, sizeof(node), 1, mf);
			}
			fclose(mf);
			printf("\n");
			while (n1 <= 0 || n1 > k)
			{
				printf("Укажите номер(№), где вы хотите внести изменения: ");
				scanf("%d", &n1);
			}
			n1--;
			printf("\n1 - тип\n");
			printf("2 - свободные места\n");
			printf("3 - цена\n");
			printf("4 - рейс\n");
			printf("5 - дата\n");
			while (n2 <= 0 || n2 > 5)
			{
				printf("Изменить: ");
				scanf("%d", &n2);
			}
			switch (n2)
			{
			case 1:
				c = 0;
				while (c != 1 && c != 2 && c != 3)
				{
					printf("1 - самолет\n2 - вертолет\n3 - аэроплан\n");
					printf("Поменять тип на: ");
					scanf("%d", &c);
				}
				arr[n1]->plane->type = c;
				break;
			case 2:
				printf("Изменить количество свободных мест на: ");
				scanf("%d", &(arr[n1]->plane->free_seat));
				break;
			case 3:
				printf("Изменить стоимость билета на: ");
				scanf("%f", &(arr[n1]->plane->ticket_price));
				break;
			case 4:
				printf("Изменить номер рейса на: ");
				scanf("%d", &(arr[n1]->fl->number));
				break;
			case 5:
				printf("Изменить дату рейса на: ");
				scanf("%s", arr[n1]->fl->date);
				break;
			}
			mf = fopen("output.bin", "r+b");
			fseek(mf, sizeof(node) * n1, SEEK_SET);
			fwrite(&arr[n1], sizeof(node), 1, mf);
			fclose(mf);
			system("cls");
			break;
		}
		case 3:
		{
			if (file_empty(mf))
			{
				printf("Файл пуст\n");
				break;
			}
			mf = fopen("output.bin", "wb");
			fclose(mf);
			for (int j = 0; j < i; j++)
				arr[j] = NULL;
			i = 0;
			printf("Файл очищен\n");
			break;
		}
		case 4:
		{
			node *b;
			int l = 0, k = 1;
			mf = fopen("output.bin", "rb");
			l = fread(&b, sizeof(node), 1, mf);
			if (!l)
			{
				printf("Данные отсутствуют\n");
				fclose(mf);
				break;
			}
			printf("№  Тип      Свободные места Цена     Рейс  Дата\n");
			while (l == 1)
			{
				if(b->plane->free_seat != 0)
					printf("%-2d %-8s %-15d %-8.2f %-5d %-10s\n", k++, aircraft_type(b->plane->type), b->plane->free_seat, b->plane->ticket_price, b->fl->number, b->fl->date);
				l = fread(&b, sizeof(node), 1, mf);
			}
			fclose(mf);
			break;
		}
		case 5:
		{
			if (file_empty(mf))
			{
				printf("Файл пуст\n");
				break;
			}
			node *b;
			int l = 0, k = 1;
			mf = fopen("output.bin", "rb");
			/*l = fread(&b, sizeof(node), 1, mf);
			if (!l)
			{
				printf("Данные отсутствуют\n");
				fclose(mf);
				break;
			}
			printf("№  Тип      Свободные места Цена     Рейс  Дата\n");
			while (l == 1)
			{
				printf("%-2d %-8s %-15d %-8.2f %-5d %-10s\n", k++, aircraft_type(b->plane->type), b->plane->free_seat, b->plane->ticket_price, b->fl->number, b->fl->date);
				l = fread(&b, sizeof(node), 1, mf);
			}
			k = 1;
			fseek(mf, 0, SEEK_SET);*/
			l = fread(&b, sizeof(node), 1, mf);
			char *temp = (char*)malloc(10 * sizeof(char));
			printf("Поиск по дате в формате дд.мм.гггг: ");
			scanf("%s", temp);
			system("cls");
			printf("№  Тип      Свободные места Цена     Рейс  Дата\n");
			while (l == 1)
			{
				if(!strcmp(temp, b->fl->date))
					printf("%-2d %-8s %-15d %-8.2f %-5d %-10s\n", k++, aircraft_type(b->plane->type), b->plane->free_seat, b->plane->ticket_price, b->fl->number, b->fl->date);
				l = fread(&b, sizeof(node), 1, mf);
			}
			if (k == 1)
			{
				system("cls");
				printf("На указанную дату рейсов нет\n");
			}
			fclose(mf);
			break;
		}
		case 6:
		{
			if (file_empty(mf))
			{
				printf("Файл пуст. Невозможно отсортировать данные\n");
				break;
			}
			node *temp;
			int L = 0, R = i - 1, h = 0, j = 0;
			while (L < R)
			{
				int j = L;
				while (j < R)
				{
					if ((arr[j]->plane->ticket_price > arr[j + 1]->plane->ticket_price) && (!strcmp(arr[j]->fl->date, arr[j + 1]->fl->date)))
					{
						temp = arr[j + 1];
						arr[j + 1] = arr[j];
						arr[j] = temp;
						h = j;
					}
					else if (strcmp(arr[j]->fl->date, arr[j + 1]->fl->date) > 0)
					{
						temp = arr[j + 1];
						arr[j + 1] = arr[j];
						arr[j] = temp;
						h = j;
					}
					j++;
				}
				R = h;
				j = R - 1;
				while (j >= L)
				{
					if ((arr[j]->plane->ticket_price > arr[j + 1]->plane->ticket_price) && (!strcmp(arr[j]->fl->date, arr[j + 1]->fl->date)))
					{
						temp = arr[j + 1];
						arr[j + 1] = arr[j];
						arr[j] = temp;
						h = j;
					}
					else if (strcmp(arr[j]->fl->date, arr[j + 1]->fl->date) > 0)
					{
						temp = arr[j + 1];
						arr[j + 1] = arr[j];
						arr[j] = temp;
						h = j;
					}
					j--;
				}
				L = h + 1;
			}
			mf = fopen("output.bin", "wb");
			for (j = 0; j < i; j++)
			{
				fwrite(&arr[j], sizeof(node), 1, mf);
			}
			fclose(mf);
			break;
		}
		case 7:
		{
			node *b;
			int l = 0, k = 1;
			mf = fopen("output.bin", "r+b");
			fseek(mf, 0, SEEK_SET);
			l = fread(&b, sizeof(node), 1, mf);
			if (!l)
			{
				printf("Данные отсутствуют\n");
				fclose(mf);
				break;
			}
			printf("№  Тип      Свободные места Цена     Рейс  Дата\n");
			while (l == 1)
			{
				printf("%-2d %-8s %-15d %-8.2f %-5d %-10s\n", k++, aircraft_type(b->plane->type), b->plane->free_seat, b->plane->ticket_price, b->fl->number, b->fl->date);
				l = fread(&b, sizeof(node), 1, mf);
			}
			printf("\n");
			fclose(mf);
			break;
		}
		case 8:
		{
			if (file_empty(mf))
			{
				printf("Файл пуст\n");
				break;
			}
			int abc;
			mf = fopen("output.bin", "r+b");
			fseek(mf, 0, SEEK_END);
			abc = ftell(mf);
			printf("Количество записей в файле: %d\n", abc / sizeof(node));
			fclose(mf);
			break;
		}
		case 100:
		{
			int k = 1;
			if (file_empty(mf))
			{
				printf("FILE_IS_EMPTY\n");
				break;
			}
			printf("№  Тип      Свободные места Цена     Рейс  Дата\n");
			for (int a = 0; a < i; a++)
				printf("%-2d %-8s %-15d %-8.2f %-5d %-10s\n", k++, aircraft_type(arr[a]->plane->type), arr[a]->plane->free_seat, arr[a]->plane->ticket_price, arr[a]->fl->number, arr[a]->fl->date);
			break;
		}
		}
	}
	system("pause");
	return 0;
}