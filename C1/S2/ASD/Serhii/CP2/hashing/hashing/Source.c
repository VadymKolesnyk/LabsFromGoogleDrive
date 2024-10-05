#include "double.h"
#include <Windows.h>
#include <time.h>
#define N 853

extern int c;

typedef struct 
{
	int n;
	list2 **array;
}hash_table;

int hash(int el);
hash_table *hash_table_init(int n);
int hash_table_add(hash_table *ht, int el);
void hash_table_print(hash_table *ht);
void hash_table_clear(hash_table *ht);
int hash_table_search(hash_table *ht, int el);
void hash_table_delel(hash_table *ht, int el);

int main()
{
	int A, B, C;
	c = 0;
	SetConsoleOutputCP(1251);
	srand(time(NULL));
	list2 *head = NULL;
	hash_table *h = hash_table_init(N);
	for (int i = 0; i < N; i++)
	{
		int el = rand()%7000;
		hash_table_add(h, el);
	}
	A = c;
	c = 0;
	hash_table_print(h);
	for (int i = 0; i < N; i++)
	{
		int el = rand() % 7000;
		hash_table_search(h, el);
	}
	B = c;
	c = 0;
	for (int i = 0; i < N; i++)
	{
		int el = rand() % 7000;
		hash_table_delel(h, el);
	}
	C = c;
	c = 0;
	hash_table_clear(h);
	printf("\n(1) = %d\n(2) = %d\n(3) = %d\n\n", A, B, C);

	/*int av = 0, min = MAXINT, max = 0;
	hash_table *h; 
	for (int kk = 0; kk < 100; kk++)
	{
		h = hash_table_init(N);
		for (int i = 0; i < N; i++)
		{
			int el = rand() % 7000;
			hash_table_add(h, el);
		}
		hash_table_clear(h);
		av += c;
		if (max < c) max = c;
		else if (min > c) min = c;
		c = 0;
	}

	/*int additionalsize = 0;
	for (int i = 0; i < N; i++)
	{
		list2 *temp = (h->array)[i];
		while (temp != NULL)
		{
			additionalsize += sizeof(temp);
			temp = temp->next;
		}
	}*/

	//printf("\nmin = %d, average = %d, max = %d\n", min, av / 100, max); 
	//printf("Размер таблицы: %d\n", N * sizeof((h->array)[0]));
	//printf("Размер дополнительной памяти: %d\n", additionalsize);
	system("pause");
}

int hash(int el)
{
	return el%N;
}

hash_table *hash_table_init(int n)
{
	hash_table *ht = (hash_table*)malloc(sizeof(hash_table));
	if (!ht)
	{
		printf("Не выделена память под хеш-таблицу\n");
		exit(0);
	}
	ht->array = (list2**)malloc(n * sizeof(list2*));
	if(!(ht->array))
	{
		printf("Не выделена память под массив\n");
		exit(0);
	}
	ht->n = N;
	for (int i = 0; i < n; i++)
		(ht->array)[i] = NULL;
	return ht;
}

int hash_table_add(hash_table *ht, int el)
{
	int j = hash(el);
	if (laddelement(&(ht->array)[j], el))
	{
		//printf("Элемент %4d успешно добавлен\n", el);
		return 1;
	}
	//printf("Элемент %4d уже есть в таблице\n", el);
	return 0;
}

void hash_table_print(hash_table *ht)
{
	for (int i = 0; i < N; i++)
	{
		printf("[%3d] ", i);
		printlist((ht->array)[i]);
	}
}

void hash_table_clear(hash_table * ht)
{
	for (int i = 0; i < N; i++)
		deletelist((ht->array)[i]);
	free(ht->array);
	free(ht);
	printf("Таблица очищена\n");
}

int hash_table_search(hash_table *ht, int el)
{
	int i = hash(el);
	if (searchlist((ht->array)[i], el))
	{
		printf("Элемент %4d найден в индексе [%3d]\n", el, i);
		return 1;
	}
	printf("Элемент %4d не найден\n", el);
	return 0;
}

void hash_table_delel(hash_table *ht, int el)
{
	int i = hash(el);
	list2 *t = (ht->array)[i];

	
	
	if (searchlist(t, el))
	{
		int temp = ldelel(&((ht->array)[i]), el);
		if (temp)
		{
			printf("Элемент %4d удален в индексе [%3d]\n", el, i);
		}
	}
}