//Автор - Колесник Вадим
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void read_matrix(char* s, int** a, int n, int m) //чтение матрицы размера n на m
{
	int b;
	FILE *f = fopen(s, "r");
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			fscanf(f, "%d", &a[i][j]);
	fclose(f);
}
void print_matrix(int** a, int n, int m) //вывод матрицы размера n на m
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			printf("%3d ", a[i][j]);
		}
		printf("\n");
	}
}
int** memoryallocation(int n, int m) //выделение памяти под матрицу размера n на m
{
	int **a = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++)
		a[i] = (int*)malloc(m * sizeof(int));


	return a;
}
int* amount(int **a, int n, int m) //подсчет кол-ва отрицательных чисел в столбцах матрицы размера n на m
{
	int* counter = (int*)malloc(m * sizeof(int));
	for (int i = 0; i < m; i++)
		counter[i] = 0;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			if (a[j][i] < 0)
				(counter[i])++;
	return counter;
}
void print_array(int* a, int n) //печать массива размера n
{
	for (int i = 0; i < n; i++)
		printf("%3d ", a[i]);
	printf("\n");
}
int main()
{
	int na = 5, ma = 5, nb = 4, mb = 5;
	int **A = memoryallocation(na, ma);
	int **B = memoryallocation(nb, mb);
	char *sa = "MatrixA.txt", *sb = "MatrixB.txt";
	read_matrix(sa, A, na, ma);
	read_matrix(sb, B, nb, mb);
	printf("A:\n");
	print_matrix(A, na, ma);
	printf("B:\n");
	print_matrix(B, nb, mb);
	int *amountA = amount(A, na, ma);
	int *amountB = amount(B, nb, mb);
	printf("A:\n");
	print_array(amountA, ma);
	printf("B:\n");
	print_array(amountB, mb);
	system("pause");
}