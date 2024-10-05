//Автор - Колесник Вадим
#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

int count(string s) // подсчет слов
{
	int count = 0;
	int i = 0;
	while (i != -1)
	{
		i++;
		i = s.find('_', i);
		count++;
	}
	return count;
}

int Cnk(int n, int k) // C из n по k
{
	int f = 1;
	for (int i = n - k + 1; i <= n; i++)
		f = f * i;
	int l = 1;
	for (int i = 1; i <= k; i++)
		l = l * i;
	return f / l;
}

int dec(string *s) // расшифровка слова
{
	double l = log((*s).length())/log(2);
	int len = (int)l;
	int c = 0;
	bool z = 1;
	if (!(l == len))
		return 1;
	for (int i = 1; i < len; i++)
	{
		c = Cnk(len, i) - 1;
		z = 1;
		for (int j = 0; j <= c; j++)
		{
			if ((*s)[i] != (*s)[i + j])
			{
				z = 0;
				break;
			}
		}
		if (z)
		{
			(*s).erase(i, c);
		}
		else
		{
			return 1;
		}
	}
	return 0;
}

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	string s, str = "";
	cout << "Введите зашифрованную строчку:" << endl;
	getline(cin, s); // 1_12_1223_12223334_1222233333344445_12222233333333334444444444555556
	int n = count(s);
	int b = 0, e = 1;
	for (int i = 1; i <= n; i++)
	{
		e = s.find('_', b);
		string s2;
		s2.assign(s, b, e - b);
		if (dec(&s2))
		{
			s2.assign(s, b, e - b);
			cout << "Ошибка, слово ‘" << s2 << "‘ не является зашифрованным" << endl;
			system("pause");
			return 1;
		}
		str = str + s2 + '_';
		b = e + 1;
	}
	str.erase(str.rfind('_'), 1);
	cout << "Результат расшифровки:" << endl << str << endl;
	system("pause");
	return 0;
}