#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	FILE *fi = fopen("input.txt", "r");
	FILE *fo = fopen("output.txt", "w");
	char *st = (char*)malloc(100 * sizeof(char));
	fprintf(fo, "Строка\tПоложительные\tОтрицательные\tНулевые\t\tСлова\n"); 
		int i = 1;
	while (!feof(fi))
	{
		fgets(st, 100, fi);
		char *str = st;
		int word = 0, pos = 0, neg = 0, nul = 0;
		char *s = NULL;
		do
		{
			s = strchr(str, ' ');
			if ((str[0] >= '1') && (str[0] <= '9'))
				pos++;
			else if (str[0] == '-')
				neg++;
			else if (str[0] == '0')
				nul++;
			else
				word++;
			str = s + 1;
		} while (s);
		fprintf(fo, "%d\t\t%d\t\t\t\t%d\t\t\t\t%d\t\t\t%d\n", i++, pos, neg, nul, word);
	}
	fclose(fi);
	fclose(fo);
	return 0;
}