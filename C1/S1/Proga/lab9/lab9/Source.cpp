//����� - �������� �����
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
	Info person[21] = { "��������",	"+380971111111",
						"��������",	"+380971111112",
						"������",	"+380971111113",
						"��������",	"+380971111114",
						"�������",	"+380971111115", 
						"������",	"+380971111116", 
						"������",	"+380971111117", 
						"������",	"+380971111118", 
						"��������",	"+380971111119", 
						"�������",	"+380971111120", 
						"�������",	"+380971111121", 
						"�������",	"+380971111122", 
						"������",	"+380971111123",
						"�����",	"+380971111124", 
						"�������",	"+380971111125", 
						"��������",	"+380971111126", 
						"��������",	"+380971111127", 
						"���",		"+380971111128", 
						"������",	"+380971111129",
						"������",	"+380971111130"};
	char sur[20], num[14];
	int i;
	printf("�������������� ������ �������:\n");
	for (i = 0; i < 20; i++)
	{
		printf("%-13s %s\n", person[i].surname, person[i].number);
	}
	printf("\n");
	printf("������� ������� � ����� ��������: ");
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
	printf("����� ������ �������:\n");
	for (i = 0; i < 21; i++)
	{
		printf("%-13s %s\n", person[i].surname, person[i].number);
	}
	system("pause");
}