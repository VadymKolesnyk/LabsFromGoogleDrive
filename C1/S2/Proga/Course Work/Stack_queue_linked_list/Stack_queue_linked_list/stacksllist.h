#pragma once
#include <stdlib.h>
typedef struct list // структура списка
{
	int key;
	struct list* next;
}sllist;
typedef struct // структура стека
{
	sllist* list;
}stacks;
int addsl(sllist** list, int key) // добавить в список
{
	sllist* temp = (sllist*)malloc(sizeof(sllist));
	if (!temp)
		return 1;
	temp->key = key;
	temp->next = *list;
	*list = temp;
	return 0;
}
int delsl(sllist** list, int* key) // удалить из списка
{
	if (!(*list))
		return 1;
	*key = (*list)->key;
	sllist *temp = (*list)->next;
	free(*list);
	*list = temp;
	return 0;
}
stacks* initsls() // инициализация стека
{
	stacks *s = (stacks*)malloc(sizeof(stacks));
	if (!s)
		return 1;
	s->list = NULL;
	return s;
}
int addsls(stacks* s, int key) // добавить в стек
{
	if (!s)
		return 1;
	if (addsl(&(s->list), key) == 1)
		return 2;
	return 0;
}
int delsls(stacks* s, int* key) // удалить из стека
{
	if (!s)
		return 1;
	if ((delsl(&(s->list), key)) == 1)
		return 2;
	return 0;
}
int printsls(stacks* s) // печать стека
{
	if (!s)
		return 1;
	if (!(s->list))
		return 2;
	sllist* temp = s->list;
	int n = 1;
	while (temp)
	{
		printf("%2d) %3d;\n", n, temp->key);
		n++;
		temp = temp->next;
	}
}
int clearsls(stacks* s) // очистка стека
{
	if (!s)
		return 1;
	int key;
	while (s->list)
	{
		delsls(s, &key);
	}
	return 0;
}
int freesls(stacks *s) // удаление стека
{
	if (!s)
		return 1;
	clearsls(s);
	free(s);
	return 0;
}