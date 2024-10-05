#define _CRT_SECURE_NO_WARNINGS
#include "linkedlist.h"
#include <stdio.h>
#include <Windows.h>
#include <time.h>

const int N = 599, MAX = 9001;
extern int c = 0, d = 0;
typedef struct
{
	int n;
	llist **array;
}hash;

hash* init(int n)
{
	hash *h = (hash*)malloc(sizeof(hash));
	if (!h)
	{
		printf("Bad allocation!\n");
		return (NULL);
	}
	h->array = (llist**)malloc(n * sizeof(llist*));
	if (!(h->array))
	{
		printf("Bad allocation!\n");
		return (NULL);
	}
	h->n = n;
	for (int i = 0; i < n; i++)
	{
		(h->array)[i] = NULL;
	}
	return h;
}

void add(hash* h, int key)
{
	int index = key % (h->n);
	(h->array)[index] = addlist((h->array)[index], key);
}

int del(hash* h, int key)
{
	int index = key % (h->n);
	(h->array)[index] = dellist((h->array)[index], key);
}

int search(hash *h, int key)
{
	int index = key % (h->n);
	if (searchlist((h->array)[index], key))
		return index;
	return -1;
}

void addN(hash *h, int max)
{		
	int min_c = MAXINT, max_c = 0; float mid_c = 0;
	int min_d = MAXINT, max_d = 0; float mid_d = 0;
	for (int n = 0; n < N; n++)
	{
		c = 0;
		d = 0;
		add(h, rand() % max);
		if (c < min_c)
			min_c = c;
		else if (c > max_c)
			max_c = c;
		if (d < min_d)
			min_d = d;
		else if (d > max_d)
			max_d = d;
		mid_c += c;
		mid_d += d;
	}
	mid_c = mid_c / N;
	mid_d = mid_d / N;
	printf("c: %d %f %d\n", min_c, mid_c, max_c);
	printf("d: %d %f %d\n", min_d, mid_d, max_d);

}

void printhash(hash* h)
{
	for (int i = 0; i < h->n; i++)
	{
		printf("hash[%3d]: ", i);
		printlist((h->array)[i]);
	}
}

void searchN(hash* h)
{
	int min_c = MAXINT, max_c = 0; float mid_c = 0;
	int min_d = MAXINT, max_d = 0; float mid_d = 0;
	for (int n = 0; n < N; n++)
	{
		c = 0;
		d = 0;
		int key = rand() % MAX;
		int index;
		if ((index = search(h, key)) != -1)
		{
		//	printf("%4d found at hash[%3d]\n", key, index);
		}
		else
		{
		//	printf("%4d didn't found\n", key);
		}
		if (c < min_c)
			min_c = c;
		else if (c > max_c)
			max_c = c;
		if (d < min_d)
			min_d = d;
		else if (d > max_d)
			max_d = d;
		mid_c += c;
		mid_d += d;
	}
	mid_c = mid_c / N;
	mid_d = mid_d / N;
	printf("c: %d %f %d\n", min_c, mid_c, max_c);
	printf("d: %d %f %d\n", min_d, mid_d, max_d);
}

void delN(hash* h)
{
	int min_c = MAXINT, max_c = 0; float mid_c = 0;
	int min_d = MAXINT, max_d = 0; float mid_d = 0;
	for (int n = 0; n < N; n++)
	{
		c = 0;
		d = 0;
		del(h, rand() % N);
		if (c < min_c)
			min_c = c;
		else if (c > max_c)
			max_c = c;
		if (d < min_d)
			min_d = d;
		else if (d > max_d)
			max_d = d;
		mid_c += c;
		mid_d += d;
	}
	mid_c = mid_c / N;
	mid_d = mid_d / N;
	printf("c: %d %f %d\n", min_c, mid_c, max_c);
	printf("d: %d %f %d\n", min_d, mid_d, max_d);
}

void delall(hash* h)
{
	for (int i = 0; i < N; i++)
		delalllist((h->array)[i]);
	free(h->array);
	free(h);
}


int main()
{
	SetConsoleOutputCP(1251);
	srand(time(NULL));
	hash* h;
	/* размер памяти
		h = init(N);
		addN(h, MAX);
		printf("%d\n", N * sizeof((h->array)[0]));
		int k = 0;
		for (int i = 0; i < N; i++)
		{
			llist* temp = (h->array)[i];
			while (temp != NULL)
			{
				k += sizeof(temp);
				temp = temp->next;
			}
		}
		printf("%d\n", k);
		delall(h);
	*/
	h = init(N);
	addN(h, MAX);
	searchN(h);
	//printhash(h);
	delN(h);
	//printhash(h);
	delall(h); 
	system("pause");
	return 0;
}