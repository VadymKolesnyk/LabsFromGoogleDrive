#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
typedef struct list
{
	int h, m;
	struct list *next;
}llist;
llist *head = NULL;
llist* create_node(int h, int m)
{
	llist *result = NULL;
	result = (llist*)malloc(sizeof(llist));
	if (result)
	{
		result->m = m;
		result->h = h;
		result->next = result;
	}
	return result;
}
int add(int h, int m)
{
	llist *k = NULL;
	k = create_node(h, m);
	if (!k) return 2; //не удалось выделить память
	if (!head)
	{
		head = k;
	}
	k->next = head;
	llist *t = head->next;
	while (t->next != head)
	{
		t = t->next;
	}
	t->next = k;
	return 0;
}
int del_first()
{
	if (!head) return 1; //не создан список
	if (head->next == head)
	{
		free(head);
		head = NULL;
		return 0;
	}
	llist *t = head->next;
	while (t->next != head)
	{
		t = t->next;
	}
	t->next = head->next;
	free(head);
	head = t->next;
	return 0;
}
int del_list()
{
	if (!head) return 1; //не создан список
	llist *t = head->next;
	while (t->next != head)
	{
		llist *temp = t->next;
		free(t);
		t = temp;
	}
	free(head);
	head = NULL;
	return 0;
}
int print_list()
{
	if (!head) return 1; //не создан список
	llist *t = head;
	do
	{
		if (t->h < 10)
		{
			printf("0%1d-", t->h);
		}
		else
		{
			printf("%2d-", t->h);
		}
		if (t->m < 10)
		{
			printf("0%1d\n", t->m);
		}
		else
		{
			printf("%2d\n", t->m);
		}
		t = t->next;
	} while (t != head);
	return 0;
}
int exchange(int k, int n)
{
	if (!head) return -1; //не создан список
	int i = 1, temp;
	if (n > k)
	{
		temp = n;
		n = k;
		k = temp;
	}
	llist *tn = head;
	while (i<n)
	{
		if (tn->next == head)
		{
			return n; //нет такого номера
		} 
		tn = tn->next;
		i++;
	}
	llist *tk = tn;
	while (i < k)
	{
		if (tk->next == head)
		{
			return k; //нет такого номера
		}
		tk = tk->next;
		i++;
	}
	temp = tn->m;
	tn->m = tk->m;
	tk->m = temp;
	temp = tn->h;
	tn->h = tk->h;
	tk->h = temp;
	return 0;
}
int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	int variant;
	int m, h, temp, i, j;
	do
	{
		printf("\nВыберите действие:\n0-выйти из программы\n1-добавить элемент в хвост списка\n2-удалить элемент с головы\n3-поменять два элемента местами\n4-напечатать весь список\n5-удалить весь список\n");
		scanf_s("%d", &variant);
		switch (variant)
		{
		case 0:
			break;
		case 1:
			printf("Введите время в формате hh mm: ");
			scanf_s("%d %d", &h, &m);
			if ((h > 23) || (h < 0) || (m > 59) || (m < 0))
			{
				printf("Введены неверные данные.\n");
				break;
			}
			temp = add(h, m);
			if (temp == 2)
			{
				printf("Не удалось выделить память.\n");
			}
			else
			{
				printf("Операция прошла успешно.\n");
			}
			break;
		case 2:
			temp = del_first();
			if (temp == 1)
			{
				printf("Не создан список.\n");
			}
			else
			{
				printf("Операция прошла успешно.\n");
			}
			break;
		case 3:
			printf("Введите номера элементов, которые нужно поменять: ");
			scanf_s("%d %d", &i, &j);
			if ((i < 1) || (j < 1))
			{
				printf("Введены неверные данные.\n");
				break;
			}
			temp = exchange(i, j);
			switch (temp)
			{
			case 0:
				printf("Операция прошла успешно.\n");
				break;
			case -1:
				printf("Не создан список.\n");
				break;
			default:
				printf("Элемента с номером %d не существует.\n", temp);
				break;
			}
			break;
		case 4:
			temp = print_list();
			if (temp)
			{
				printf("Не создан список.\n");
			}
			break;
		case 5:
			del_list();
			printf("Список удален.\n");
			break;
		default:
			printf("Введено неверное значение.\n");
			break;
		}
	} while (variant != 0);
	return 0;
}