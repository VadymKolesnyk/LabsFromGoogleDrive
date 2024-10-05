//Автор - Колесник Вадим
#define	_CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	FILE *f = fopen("input.txt", "r");
	char *s = (char*)malloc(100 * sizeof(char));
	int i = 0;
	fgets(s, "%s", f);
	printf("input.txt:\n");
	printf("%s\n", s);
	char *c = strstr(s, "abcd");
	while (c)
	{
		strcpy(c, c + 4);
		c = strstr(c, "abcd");
	}
	printf("New string:\n");
	printf("%s\n", s);
	system("pause");
	return 0;
}