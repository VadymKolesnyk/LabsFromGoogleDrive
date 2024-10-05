#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

void print_str(string *a, int n)
{
	for (int i = 0; i < n; i++)
	{
		if (i != n - 1)
			cout << a[i] << '_';
		else
			cout << a[i] << endl;
	}
}

void swap(string &x, string &y)
{
	string temp = x;
	x = y;
	y = temp;
}

void perestan(int j, string *a, int words)
{
	if (j == words)
	{
		print_str(a, words);
		return;
	}

	for (int i = j; i < words; i++)
	{
		swap(a[j], a[i]);
		perestan(j + 1, a, words);
		swap(a[j], a[i]);
	}
}

int count(string str1)
{
	int underscore, n = 0;
	while ((str1.find('_', 0)) != -1)
	{
		underscore = str1.find('_', 0);
		str1.erase(0, underscore + 1);
		n++;
	}
	return n;
}

void fill_array(string str, string *arr, int n)
{
	int us, i = 0;
	string t;
	while ((str.find('_')) != -1)
	{
		us = str.find('_', 0);
		t.assign(str, 0, us);
		str.erase(0, us + 1);
		arr[i] = t;
		i++;
	}
}

void main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	string s1, workstr, temp;
	char c = '_';
	int pos, words;
	cout << "Введите предложение, содержащее '_' вместо пробелов: ";
	cin >> s1; 
	cout << "Полученная строка: " << s1 << endl;
	workstr = s1;
	words = count(workstr + '_');
	cout << "Количество слов в строке: " << words << endl;
	string *array = new string[words];
	fill_array(workstr + '_', array, words);
	cout << "Перестановки слов:" << endl;
	perestan(0, array, words);
	system("pause");
}