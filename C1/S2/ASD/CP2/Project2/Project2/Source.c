#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <time.h>

const int N = 599, MAX = 9001;
extern int c = 0, d = 0;
typedef struct
{
	int n;
	int *array;
}hash;

hash* init(int n)
{
	hash *h = (hash*)malloc(sizeof(hash));
	if (!h)
	{
		printf("Bad allocation!\n");
		return (NULL);
	}
	h->array = (int*)malloc(n * sizeof(int));
	if (!(h->array))
	{
		printf("Bad allocation!\n");
		return (NULL);
	}
	h->n = n;
	for (int i = 0; i < n; i++)
	{
		(h->array)[i] = -1;
	}
	return h;
}

void add(hash* h, int key)
{
	c++;
	if (key == (h->array)[key])
	{
	//	printf("%4d has already been added\n", key);
	}
	else
	{
		d++;
		(h->array)[key] = key;
	//	printf("%4d was successfully added\n", key);
	}
}

int del(hash* h, int key)
{
	c++;
	if (key == (h->array)[key])
	{
	//	printf("%4d was successfully deleted\n", key);
		d++;
		(h->array)[key] = -1;
	}
	else
	{
	//	printf("%4d cannot be deleted\n", key);
	}
}

int search(hash *h, int key)
{
	c++;
	if (key == (h->array)[key])
		return key;
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
		if ((h->array)[i] != -1)
		{
			printf("hash[%4d]: %4d\n", i, (h->array)[i]);
		}
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
		if (search(h, key) != -1)
		{
		//	printf("%4d found at hash[%3d]\n", key, key);
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
		del(h, rand() % MAX);
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
	free(h->array);
	free(h);
}

int main()
{
	SetConsoleOutputCP(1251);
	srand(time(NULL));
	hash* h;

	//{
	//	h = init(MAX); // память
	//	addN(h, MAX);
	//	printf("%d\n", (MAX) * sizeof((h->array)[0]));
	//	delall(h);
	//}
	h = init(MAX);
	addN(h, MAX);
	//printhash(h);
	searchN(h);
	delN(h);
	//printhash(h);
	delall(h);
	system("pause");
	return 0;
}