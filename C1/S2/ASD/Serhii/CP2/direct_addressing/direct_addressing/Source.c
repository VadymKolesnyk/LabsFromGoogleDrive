#include <Windows.h>
#include <time.h>
#include <stdio.h>
#define N 853
#define MAX 7001

int c = 0;

typedef struct
{
	int n;
	int *array;
}hash_table;

hash_table *hash_table_init(int n);
void hash_table_add(hash_table *ht, int el);
void hash_table_print(hash_table *ht, int n);
void hash_table_clear(hash_table *ht);
int hash_table_search(hash_table *ht, int el);
void hash_table_delel(hash_table *ht, int el);

int main()
{
	SetConsoleOutputCP(1251);
	srand(time(NULL));
	hash_table *h = hash_table_init(MAX);
	for (int i = 0; i < N; i++)
	{
		int el = rand() % 7000;
		hash_table_add(h, el);
	}
	hash_table_print(h, MAX);
	for (int i = 0; i < N; i++)
	{
		int el = rand() % 7000;
		hash_table_search(h, el);
	}
	for (int i = 0; i < N; i++)
	{
		int el = rand() % 7000 + 1;
		hash_table_delel(h, el);
	}
	hash_table_clear(h);
	/*int av = 0, min = MAXINT, max = 0;
	hash_table *h;
	for (int kk = 0; kk < 100; kk++)
	{
		h = hash_table_init(MAX);
		for (int i = 0; i < N; i++)
		{
			int el = rand() % 7001;
			hash_table_add(h, el);
		}
		c = 0;
		for (int i = 0; i < N; i++)
		{
			int el = rand() % 7001;
			hash_table_delel(h, el);
		}
		//hash_table_print(h, MAX);
		av += c;
		if (max < c) max = c;
		else if (min > c) min = c;
		c = 0;
		hash_table_clear(h);
	}
	printf("\nmin = %d, average = %d, max = %d\nРазмер таблицы: %d\n", min, av / 100, max, MAX * sizeof((h->array)[0]));*/
	system("pause");
}

hash_table *hash_table_init(int n)
{
	hash_table *ht = (hash_table*)malloc(sizeof(hash_table));
	if (!ht)
	{
		printf("Не выделена память под хеш-таблицу\n");
		exit(0);
	}
	ht->array = (int*)malloc(n * sizeof(int));
	if (!(ht->array))
	{
		printf("Не выделена память под массив\n");
		exit(0);
	}
	ht->n = n;
	for (int i = 0; i < n; i++)
		(ht->array)[i] = -1;
	return ht;
}

void hash_table_add(hash_table *ht, int el)
{
	c++;
	if ((ht->array)[el] == -1)
		(ht->array)[el] = el;
	else
		printf("Такой элемент уже добавлен\n");
}

void hash_table_print(hash_table *ht, int n)
{
	for (int i = 0; i < n; i++)
	{
		if ((ht->array)[i] != -1)
			printf("%4d\n", (ht->array)[i]);
	}
}

void hash_table_clear(hash_table * ht)
{
	free(ht->array);
	free(ht);
	printf("Таблица очищена\n");
}

int hash_table_search(hash_table *ht, int el)
{
	c++;
	if ((ht->array)[el] != -1)
	{
		printf("Элемент %4d найден в индексе [%4d]\n", el, el);
		return 1;
	}
	printf("Элемент %4d не найден\n", el);
	return 0;
}

void hash_table_delel(hash_table *ht, int el)
{
	c++;
	if ((ht->array)[el] != -1)
	{
		printf("Элемент %4d удален в индексе [%4d]\n", el, el);
		(ht->array)[el] = -1;
	}
	else
		printf("Элемента %4d не существует\n", el);
}