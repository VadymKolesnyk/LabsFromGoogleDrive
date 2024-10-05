#pragma once
#include <stdlib.h>
typedef struct list // ��������� ������
{
	int key;
	struct list* next;
}sllist;
typedef struct // ��������� �����
{
	sllist* list;
}stacks;
int addsl(sllist** list, int key) // �������� � ������
{
	sllist* temp = (sllist*)malloc(sizeof(sllist));
	if (!temp)
		return 1;
	temp->key = key;
	temp->next = *list;
	*list = temp;
	return 0;
}
int delsl(sllist** list, int* key) // ������� �� ������
{
	if (!(*list))
		return 1;
	*key = (*list)->key;
	sllist *temp = (*list)->next;
	free(*list);
	*list = temp;
	return 0;
}
stacks* initsls() // ������������� �����
{
	stacks *s = (stacks*)malloc(sizeof(stacks));
	if (!s)
		return 1;
	s->list = NULL;
	return s;
}
int addsls(stacks* s, int key) // �������� � ����
{
	if (!s)
		return 1;
	if (addsl(&(s->list), key) == 1)
		return 2;
	return 0;
}
int delsls(stacks* s, int* key) // ������� �� �����
{
	if (!s)
		return 1;
	if ((delsl(&(s->list), key)) == 1)
		return 2;
	return 0;
}
int printsls(stacks* s) // ������ �����
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
int clearsls(stacks* s) // ������� �����
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
int freesls(stacks *s) // �������� �����
{
	if (!s)
		return 1;
	clearsls(s);
	free(s);
	return 0;
}