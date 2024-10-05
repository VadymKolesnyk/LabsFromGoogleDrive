#pragma once
#include <stdio.h>
#include <stdlib.h>
typedef struct list
{
	int key;
	struct list *next;
}llist;
int c, d;
llist* create_node(int key)
{
	llist *result = NULL;
	result = (llist*)malloc(sizeof(llist));
	if (result)
	{
		d++;
		result->key = key;
		result->next = NULL;
	}
	return result;
}

llist* addlist(llist *head, int key)
{
	llist *k = NULL;
	k = create_node(key);
	if (!k) return k;
	c++;
	if (!head)
	{
		d++;
		//printf("%4d successfully added\n", key);
		return k;
	}
	llist *t = head;
	while (t->next != NULL)
	{
		c++;
		if (t->key == key)
		{
			//printf("%4d has already been added\n", key);
			return head;
		}
		d++;
		t = t->next;
	}
	c++;
	if (t->key == key)
	{
		//printf("%4d has already been added\n", key);
		return head;
	}
	t->next = k;
	d++;
	//printf("%4d successfully added\n", key);
	return head;
}

llist* searchlist(llist *head, int key)
{
	llist *t = head;
	c++;
	while (t != NULL)
	{
		c++;
		if (t->key == key)
			return t;
		d++;
		t = t->next;
	}
	return (NULL);
}
llist* dellist(llist *head, int key)
{
	c++;
	if (!head)
	{
	//	printf("%4d cannot be deleted\n", key);
		return (NULL);
	}
	c++;
	if (head->key == key)
	{
		llist *temp = head;
		d++;
		head = head->next;
		free(temp);
	//	printf("%4d was successfully deleted\n", key);
		return head;
	}
	llist *t = head;
	while (t->next != NULL)
	{
		c++;
		if (t->next->key == key)
		{
			llist *temp = t->next;
			t->next = t->next->next;
			free(temp);
		//	printf("%4d was successfully deleted\n", key);
			return head;
		}
		d++;
		t = t->next;
	}
	//printf("%4d cannot be deleted\n", key);
	return head;
}
llist* delalllist(llist *head)
{
	if (!head) return (NULL);
	llist *t = head;
	while (t != NULL)
	{
		llist *temp = t;
		t = t->next;
		free(temp);
	}
	return (NULL);
}
int printlist(llist *head)
{
	llist *t = head;
	while (t != NULL)
	{
		printf("%4d -> ", t->key);
		t = t->next;
	}
	printf("/\n");
	return 0;
}