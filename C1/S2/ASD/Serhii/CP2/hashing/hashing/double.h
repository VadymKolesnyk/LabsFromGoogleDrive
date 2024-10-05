#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>

int c;

typedef struct list
{
	struct list *prev, *next;
	int key;
}list2;

list2* lcreate_node(int n)
{
	list2 *newspisok = (list2*)malloc(sizeof(list2));
	if (newspisok)
	{
		newspisok->prev = NULL;
		newspisok->next = NULL;
		newspisok->key = n;
	}
	return (newspisok);
}

list2* lgettail(list2 *head)
{
	list2 *temp = head;
	if (temp == NULL)
		return temp;
	while (temp->next != NULL)
		temp = temp->next;
	return temp;
}

int searchlist(list2 *head, int n)
{
	list2 *temp = head;
	while (temp != NULL)
	{
		c++;
		if (temp->key == n)
			return 1;
		temp = temp->next;
	}
	return 0;
}

int *laddelement(list2 **head, int n)
{
	list2 *temp = NULL;
	temp = lcreate_node(n);
	if (!temp) return 0;
	c++;
	if (!*head)
	{
		*head = temp;
		return 1;
	}
	if (searchlist(*head, n) == 1) return 0;
	list2 *t = lgettail(*head);
	t->next = temp;
	temp->prev = t;
	temp->next = NULL;
	return 1;
}

int printlist(list2 *head)
{
	list2 *temp = NULL;
	temp = head;
	if (temp == NULL)
	{
		printf("NULL\n");
		return 0;
	}
	while (temp != NULL)
	{
		printf("%d -> ", temp->key);
		temp = temp->next;
	}
	printf("NULL\n");
	return 1;
}

list2 *deletelist(list2 *head)
{
	list2 *tail = lgettail(head);
	if (tail == NULL)
	{
		//printf("Список пуст");
		return NULL;
	}
	list2* temp = NULL;
	while (tail != NULL)
	{
		temp = tail;
		if (tail->prev == NULL)
		{
			tail = NULL;
			head = NULL;
			free(temp);
			//printf("Список очищен");
			return head;
		}
		tail = tail->prev;
		tail->next = NULL;
		free(temp);
	}
	return NULL;
}

int ldelel(list2 **head, int n)
{
	list2 *temp = *head;
	if (temp == NULL)
		return 0;
	while (temp != NULL)
	{
		if (temp->key == n)
		{
			if ((temp->prev == NULL) && (temp->next == NULL))
			{
				free(temp);
				*head = NULL;
				return 1;
			}
			if (temp->prev == NULL)
			{
				*head = (*head)->next;
				free(temp);
				(*head)->prev = NULL;
				return 1;
			}
			if (temp->next == NULL)
			{
				list2 *tail = temp->prev;
				tail->next = NULL;
				free(temp);
				return 1;
			}
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			free(temp);
			return 1;
		}
		temp = temp->next;
	}
	return 0;
}