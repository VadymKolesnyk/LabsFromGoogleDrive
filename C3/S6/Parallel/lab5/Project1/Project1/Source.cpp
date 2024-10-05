//#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

int main()
{
	int authentication = 0;
	char cUsername[10] = "111111111", cPassword[10] = "222222222"; // дадим им начальную инициализацию, чтоб было видно, где под них была выделена память
	
	// поиск максимального и минимального байта, что выделенны под эти переменные
	char* min = (char*)&authentication > cUsername ? cUsername : (char*)&authentication;
	min = min > cPassword ? cPassword : min;

	char* max = (char*)(&authentication) + 3 < cUsername + 9 ? cUsername + 9 : (char*)(&authentication) + 3;
	max = max < cPassword + 9 ? cPassword + 9 : max;

	char* a = min;
	for (int i = 0; i <= max - min; i++)
	{
		printf("%3u | %u\n", (unsigned char)(*(a + i)), a + i);
	}

	printf("\nPassword: %u\nUsername: %u\nAuth: %u\n", cPassword, cUsername, &authentication); // вывод адрессов переменных

	scanf_s("%s", cUsername);
	scanf_s("%s", cPassword);

	//scanf("%9s", cUsername);
	//rewind(stdin);
	//scanf("%9s", cPassword);
	//rewind(stdin);



	for (int i = 0; i <= max - min; i++)
	{
		printf("%3u | %u\n", (unsigned char)(*(a + i)), a + i);
	}


	printf("Password: %s\nUsername: %s\nAuth: %d\n",cPassword, cUsername, authentication); // вывод самих переменных

	if (strcmp(cUsername, "admin") == 0 && strcmp(cPassword, "adminpass"))
	{
		authentication = 1;
	}

	if (authentication)
	{
		printf("Access");
	}
	else
	{
		printf("Wrong");
	}
	return 0;
}