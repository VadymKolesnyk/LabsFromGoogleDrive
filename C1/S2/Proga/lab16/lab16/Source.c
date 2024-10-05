#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#define begin {
#define end }

#define chislo 0
#define kolichestvo 1

#define OUTPUT

int main()
	begin
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
#define a number
	int n;
#ifdef OUTPUT // вывод при определении OUTPUT
	printf("Введите количество чисел в масиве n = ");
#endif // OUTPUT
	scanf("%d", &n);
#ifdef OUTPUT // вывод при определении OUTPUT
	printf("Введите масив через пробел:\n");
#endif // OUTPUT
	int *a = (int*)malloc(n * sizeof(int)); // выделение память под масив
	for (int i = 0; i < n; i++) // ввод масива с клавиатуры
		begin
		scanf("%d", &a[i]);
		end
	int **b = (int**)malloc(n * sizeof(int*)); // выделение память под вспомогательный масив
	for (int i = 0; i < n; i++)
		begin
		b[i] = (int*)malloc(2 * sizeof(int));
		end
	int k = 0;
	for (int i = 0; i < n; i++)
		begin
		int z = 1; // флаг надо ли добавлять новый элемент в впомагательный масив
		for (int j = 0; j < k; j++)
			begin
			if (a[i] == b[j][chislo])
				begin
				b[j][kolichestvo]++;
				z = 0;
				break;
				end
			end
		if (z)
			begin
			b[k][chislo] = a[i];
			b[k][kolichestvo] = 1;
			k++;
			end
		end
#ifdef OUTPUT // вывод при определении OUTPUT
	printf("Количество вхождений в масив каждого из элементов:\n");
#endif // OUTPUT
	for (int i = 0; i < k; i++) // вывод количества вхождений в масив каждого из элементов
		begin
		printf("%d  - %d р.\n", b[i][chislo], b[i][kolichestvo]);
		end

#undef a
#define a str
	char a[100];
#ifdef OUTPUT // вывод при определении OUTPUT
		printf("Введите строку до 99 символов:\n");
#endif // OUTPUT
	scanf("%s", a);
#ifdef OUTPUT // вывод при определении OUTPUT
	printf("Введите код символа, который надо найти: k = ");
#endif // OUTPUT
	scanf("%d", &n);
	int z = 1; // флаг найден ли символ
	for (int i = 0; a[i] != '\0'; i++)
		begin
		if (a[i] == n) // поиск символа
			begin
			printf("Символ найден с индексом %d\n", i);
			z = 0;
			break;
			end
		end
	if (z)
		begin
		printf("Символ не найден\n");
		end
	system("pause");
	end