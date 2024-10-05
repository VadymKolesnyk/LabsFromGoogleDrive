#pragma once
#include <stdlib.h>
typedef struct dlistp // структура списка
{
	int key;
	int priority;
	struct dlistp* next;
	struct dlistp* previous;
}dllistp;
typedef struct // структура очереди
{
	dllistp* list;
}queue;

int adddlp(dllistp** list, int key, int priority) // добавить в список
{
	dllistp* temp = (dllistp*)malloc(sizeof(dllistp));
	if (!temp)
		return 1;
	temp->key = key;
	temp->priority = priority;
	temp->next = NULL;
	temp->previous = NULL;
	if (!(*list))
	{
		*list = temp;
		return 0;
	}
	dllistp* t = *list;
	dllistp* tp = NULL;
	while (t) // поиск места для вставки в список по приоритету
	{
		if (t->priority < temp->priority)
		{
			temp->previous = t->previous;
			temp->next = t;
			t->previous = temp;
			if (temp->previous)
			{
				temp->previous->next = temp;
			}
			else
			{
				*list = temp;
			}
			return 0;
		}
		tp = t;
		t = t->next;
	}
	tp->next = temp;
	temp->previous = tp;
	return 0;
}
int deldlp(dllistp** list, int* key) // удалить из списка
{
	if (!(*list))
		return 1;
	*key = (*list)->key;
	dllistp *temp = (*list)->next;
	free(*list);
	*list = temp;
	if (*list)
		(*list)->previous = NULL;
	return 0;
}

queue* initq() // инициализация очереди
{
	queue* q = (queue*)malloc(sizeof(queue));
	if (!q)
		return NULL;
	q->list = NULL;
	return q;
}

int addq(queue* q, int key, int priority) // добавить в очередь
{
	if (!q)
		return 1;
	if (adddlp(&(q->list), key, priority) == 1)
		return 2;
	return 0;
}

int delq(queue* q, int* key) // удалить из очереди
{
	if (!q)
		return 1;
	if (deldlp(&(q->list), key) == 1)
		return 2;
	return 0;
}
char* prior(int n) // определение приоритета
{
	if (n == 1)
		return "низкий";
	if (n == 2)
		return "средний";
	if (n == 3)
		return "высокий";
	return NULL;
}
int printq(queue* q) // печать очереди
{
	if (!q)
		return 1;
	if (!(q->list))
		return 2;
	dllistp* temp = q->list;
	int n = 1;
	while (temp)
	{
		printf("%2d) %3d;\t %s приоритет\n", n, temp->key, prior(temp->priority));
		n++;
		temp = temp->next;
	}
}
int clearq(queue* q) // очистить очередь
{
	if (!q)
		return 1;
	int key;
	while (q->list)
	{
		delq(q, &key);
	}
	return 0;
}
int freeq(queue *q) // удалить очередь
{
	if (!q)
		return 1;
	clearq(q);
	free(q);
	return 0;
}