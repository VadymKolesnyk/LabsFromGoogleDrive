#pragma once
#include <stdlib.h>
typedef struct dlist // ��������� ������
{
	int key;
	struct dlist* next;
	struct dlist* previous;
}dllist;
typedef struct // ��������� �����
{
	dllist* list;
}stackd;

int adddl(dllist** list, int key) // �������� � ������
{
	dllist* temp = (dllist*)malloc(sizeof(dllist));
	if (!temp)
		return 1;
	temp->key = key;
	temp->next = *list;
	temp->previous = NULL;
	if (*list) 
		(*list)->previous = temp;
	*list = temp;
	return 0;
}

int deldl(dllist** list, int* key) // ������� �� ������
{
	if (!(*list))
		return 1;
	*key = (*list)->key;
	dllist *temp = (*list)->next;
	free(*list);
	*list = temp;
	if (*list)
		(*list)->previous = NULL;
	return 0;
}

stackd* initdls() // ������������� �����
{
	stackd* s = (stackd*)malloc(sizeof(stackd));
	if (!s)
		return 1;
	s->list = NULL;
	return s;
}

int adddls(stackd* s, int key) // �������� � ����
{
	if (!s)
		return 1;
	if (adddl(&(s->list), key) == 1)
		return 2;
	return 0;
}

int deldls(stackd* s, int* key) // ������� �� �����
{
	if (!s)
		return 1;
	if ((deldl(&(s->list), key)) == 1)
		return 2;
	return 0;
}
int printdls(stackd* s) // ������ �����
{
	if (!s)
		return 1;
	if (!(s->list))
		return 2;
	dllist* temp = s->list;
	int n = 1;
	while (temp)
	{
		printf("%2d) %3d;\n", n, temp->key);
		n++;
		temp = temp->next;
	}
}
int cleardls(stackd* s) // ������� �����
{
	if (!s)
		return 1;
	int key;
	while (s->list)
	{
		deldls(s, &key);
	}
	return 0;
}
int freedls(stackd *s) // �������� �����
{
	if (!s)
		return 1;
	cleardls(s);
	free(s);
	return 0;
}