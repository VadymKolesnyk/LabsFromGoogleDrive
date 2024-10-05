//Автор - Колесник Вадим
#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <string.h>
#include <Windows.h>

int main()  
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	struct Info
	{
		char surname[20];
		char number[14];
	};
	Info person[21] = { "Богданов",	"+380971111111",
						"Васильев",	"+380971111112",
						"Волков",	"+380971111113",
						"Воробьев",	"+380971111114",
						"Голубев",	"+380971111115", 
						"Зайцев",	"+380971111116", 
						"Иванов",	"+380971111117", 
						"Козлов",	"+380971111118", 
						"Кузнецов",	"+380971111119", 
						"Лебедев",	"+380971111120", 
						"Морозов",	"+380971111121", 
						"Новиков",	"+380971111122", 
						"Павлов",	"+380971111123",
						"Попов",	"+380971111124", 
						"Семенов",	"+380971111125", 
						"Соловьев",	"+380971111126", 
						"Харламов",	"+380971111127", 
						"Щур",		"+380971111128", 
						"Ющенко",	"+380971111129",
						"Якутов",	"+380971111130"};
	char sur[20], num[14];
	int i;
	printf("Первоначальный массив записей:\n");
	for (i = 0; i < 20; i++)
	{
		printf("%-13s %s\n", person[i].surname, person[i].number);
	}
	printf("\n");
	printf("Введите фамилию и номер телефона: ");
	scanf("%s", sur);
	scanf("%s", num);
	i = 19;
	while ((strcmp(person[i].surname, sur) > 0) && (i >= 0))   
	{
		person[i + 1] = person[i];
		i--; 
	}
	strcpy_s(person[++i].surname, sur);
	strcpy_s(person[i].number, num);
	printf("\n");
	printf("Новый массив записей:\n");
	for (i = 0; i < 21; i++)
	{
		printf("%-13s %s\n", person[i].surname, person[i].number);
	}
	system("pause");
}