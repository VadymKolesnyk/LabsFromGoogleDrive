#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "stacksllist.h" // Стек в односвязном списке
#include "stackdllist.h" // Стек в двусвязном списке
#include "queuedllist.h" // Очередь с приоритетами в двусвязном списке

int main()
{
	SetConsoleOutputCP(1251);
	int v = -1;
	while (v)
	{
		printf("0 - Выход из програмы\n");
		printf("1 - Стек в односвязном списке\n");
		printf("2 - Стек в двусвязном списке\n");
		printf("3 - Очередь с приоритетами в двусвязном списке\n");
		scanf("%d", &v);
		system("cls");
		if (v == 1)
		{
			stacks *st = initsls(); // инициализация стека
			int s = -1;
			if (!st)
			{
				printf("Не удалось выделить память под стек\n");
				s = 0;
			}
			while (s)
			{
				printf("0 - Назад\n");
				printf("1 - Добавить в стек\n");
				printf("2 - Удалить из стека\n");
				printf("3 - Печать стека\n");
				printf("4 - Очистить стек\n");
				scanf("%d", &s);
				system("cls");
				if (s == 1)
				{
					printf("Введите число, key=");
					int key;
					scanf("%d", &key);
					if (addsls(st, key) == 2) // добавнелие в стек
					{
						printf("Не удалось выделить память под элемент\n");
					}
					else
					{
						printf("%d добавлен в стек\n", key);
					}
				}
				else if (s == 2)
				{
					int key = 0;
					if (delsls(st, &key) == 2) // удаление из стека
					{
						printf("Cтек пуст\n");
					}
					else
					{
						printf("%d удален из стека\n", key);
					}
				}
				else if (s == 3)
				{
					if (printsls(st) == 2) // вывод на экран стека
					{
							printf("Cтек пуст\n");
					}
				}
				else if (s == 4)
				{
					clearsls(st); // очищение стека
					printf("Cтек очищен\n");
				}
			}
			freesls(st); // удалить стек
		}
		else if (v == 2)
		{
			stackd *st = initdls(); // инициализация стека
			int s = -1;
			if (!st)
			{
				printf("Не удалось выделить память под стек\n");
				s = 0;
			}
			while (s)
			{
				printf("0 - Назад\n");
				printf("1 - Добавить в стек\n");
				printf("2 - Удалить из стека\n");
				printf("3 - Печать стека\n");
				printf("4 - Очистить стек\n");
				scanf("%d", &s);
				system("cls");
				if (s == 1)
				{
					printf("Введите число, key=");
					int key;
					scanf("%d", &key);
					if (adddls(st, key) == 2) // добавнелие в стек
					{
						printf("Не удалось выделить память под элемент\n");
					}
					else
					{
						printf("%d добавлен в стек\n", key);
					}
				}
				else if (s == 2)
				{
					int key = 0;
					if (deldls(st, &key) == 2) // удаление из стека
					{
						printf("Cтек пуст\n");
					}
					else
					{
						printf("%d удален из стека\n", key);
					}
				}
				else if (s == 3)
				{
					if (printdls(st) == 2) // вывод на экран стека
					{
						printf("Cтек пуст\n");
					}
				}
				else if (s == 4)
				{
					cleardls(st); // очищение стека
					printf("Cтек очищен\n");
				}
			}
			freedls(st); // удалить стек
		}
		else if (v == 3)
		{
			queue *q = initq(); // инициализация очереди
			int s = -1;
			if (!q)
			{
				printf("Не удалось выделить память под очередь\n");
				s = 0;
			}
			while (s)
			{
				printf("0 - Назад\n");
				printf("1 - Добавить в очередь\n");
				printf("2 - Удалить из очереди\n");
				printf("3 - Печать очереди\n");
				printf("4 - Очистить очередь\n");
				scanf("%d", &s);
				system("cls");
				if (s == 1)
				{
					printf("Введите число, key=");
					int key;
					scanf("%d", &key);

					int p = 0;
					while (p != 1 && p != 2 && p != 3)
					{
						printf("Выберите приоритет:\n");
						printf("1 - низкий\n");
						printf("2 - средний\n");
						printf("3 - высокий\n");
						scanf("%d", &p);
					}
					if (addq(q, key, p) == 2) // добавление в очередь
					{
						printf("Не удалось выделить память под элемент\n");
					}
					else
					{
						printf("%d добавлен в очередь\n", key);
					}
				}
				else if (s == 2)
				{
					int key = 0;
					if (delq(q, &key) == 2) // удаление из очереди
					{
						printf("Очередь пуста\n");
					}
					else
					{
						printf("%d удален из очереди\n", key);
					}
				}
				else if (s == 3)
				{
					if (printq(q) == 2) // вывод очереди на экран
					{
						printf("Очередь пуста\n");
					}
				}
				else if (s == 4)
				{
					clearq(q); // очистка очереди
					printf("Очередь очищена\n");
				}
			}
			freeq(q); // удалить очередь
		}
	}
	return 0;
}
